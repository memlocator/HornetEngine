--[[
	Project template to set up a new 3D renderer scene
	
	Root object is in the variable 'GameObject'. Anything put inside this hierarchy is treated as a live game object.

	The engine is primarily a "subscription based" model where functionality is optional and needs to be subscribed to by
	making an object that handles it. An example would be a 3D render pipeline with a "GlowingSceneOperation" object.
]]

print "starting project"

-- Create a home for mesh assets & load meshes in from a json file
local meshes = GameObject.Object()
meshes.Name = "Meshes"
meshes.Parent = Engine

local assets
print("pcall", pcall(function() assets = json.decode("./assets/json/mapAssets.json", true) end))

for name, path in pairs(assets.meshes) do
	print(name, path)
	GameObject.MeshLoader.NewAsset(name, path).Parent = meshes
	print("loaded", name)
end

-- Create a home for textures
local textures = GameObject.Textures()
textures.Name = "Textures"
textures.Parent = Engine


--[[
	Set up the effective game world. At the moment these don't do anything yet, but they are planned for use in controlling
	the simulation state. All live objects that are meant to be rendered or simulate something should be stored here.
]]
local environments = GameObject.Environments()
environments.Parent = Engine

local level = GameObject.Environment()
level.Name = "Level"
level.Parent = environments

local simulation = GameObject.Simulation()
simulation.Parent = level

--[[
	Initialize the global light that will be used to light up the scene.
	This is entirely optional, but it is good to set one up if you don't make any other lights and want to be able to see
	objects as anything other than black silhouettes.
]]

local skyLight = GameObject.Light()
skyLight.Enabled = true
skyLight.Direction = Vector3(0.25, -1, 0.25):Unit()
skyLight.Brightness = 0.5
skyLight.Diffuse = RGBA(1, 1, 1, 1)
skyLight.Specular = RGBA(1, 1, 1, 1)
skyLight.Ambient = RGBA(1, 1, 1, 1)
skyLight.Type = Enum.LightType.Directional
skyLight.Parent = simulation

-- Initialize the camera that will be used to render the scene. This can be moved around by script however you want.
local resolution = GameObject.FrameBuffer.WindowSize

local aspectRatio = resolution.Width / resolution.Height
local size = 5 / 3
local defaultWidth = aspectRatio * size
local defaultHeight = size
local defaultProjection = 1
local defaultNear = 0.1
local defaultFar = 5000

local camera = GameObject.Camera()
camera.Parent = level --[[ camera:SetParent(level) ]]
camera:SetProperties(defaultWidth, defaultHeight, defaultProjection, defaultNear, defaultFar)
camera:SetTransformation(Matrix3(0, 5, 10))

--[[
	Initialize the scene where objects are tracked for rendering purposes.
	It's primary purpose is to serve as an acceleration structure for render related lookups & to hold live render objects.
	If you want an object to render it has to be registered with `scene:AddObject(Model)`.
	If you want a light to illuminate the scene it has to be registered with `scene:AddLight(Light)`, except for the global light.
]]
local scene = GameObject.Scene()
scene.Parent = level
scene.CurrentCamera = camera
scene.GlobalLight = skyLight

-- Initialize the render pipeline
--[[
	This object is responsible for rendering objects to either the screen or a desired output FrameBuffer.
	A FrameBuffer can be used for render to texture, to render onto another object, or even saving to file (don't remember the state of this one lol)
]]
local sceneDraw = GameObject.GlowingSceneOperation()
sceneDraw.Parent = level
sceneDraw:Configure(resolution.Width, resolution.Height, scene)
sceneDraw.Radius = 10
sceneDraw.Sigma = 20
sceneDraw.SkyBrightness = 1
sceneDraw.SkyBackgroundBrightness = 1
sceneDraw.SkyColor = RGBA(15/255, 5/255, 15/255, 1)
sceneDraw.SkyBackgroundColor = RGBA(1, 0, 0, 0)
sceneDraw.Resolution = Vector3(resolution.Width, resolution.Height)
sceneDraw.RenderAutomatically = true

local screen = GameObject.DeviceTransform()
screen.Size = DeviceVector(0, resolution.Width, 0, resolution.Height)
screen.Parent = level

local ui = GameObject.InterfaceDrawOperation()
ui.CurrentScreen = screen
ui.RenderAutomatically = true
ui.Parent = level

local input = GameObject.InputContext()
input.Device = screen
input.InputSource = Engine.GameWindow.UserInput
input.Parent = ui

local tileTexture = textures.Create("./assets/textures/minesweeper_tiles.png", Enum.SampleType.Nearest)

local lower = 0.5
local upper = 1

local tileOffsets = {
	Vector3(0, lower), -- Unknown
	Vector3(0, upper), -- Pressed
	Vector3(1/7, lower), -- Flagged
	Vector3(2/7, lower), -- Mine
	Vector3(2/7, upper), -- Blown Mine
	Vector3(1/7, upper), -- Clear
	Vector3(3/7, lower), -- 1
	Vector3(3/7, upper), -- 2
	Vector3(4/7, lower), -- 3
	Vector3(4/7, upper), -- 4
	Vector3(5/7, lower), -- 5
	Vector3(5/7, upper), -- 6
	Vector3(6/7, lower), -- 7
	Vector3(6/7, upper) -- 8
}

local TileTypes = {
	Unknown = 1,
	Pressed = 2,
	Flagged = 3,
	Mine = 4,
	BlownMine = 5,
	Clear = 6,
	Neighbors0 = 6, -- For getting the correct texture with math: Neighbors0 + num
	Neighbors1 = 7,
	Neighbors2 = 8,
	Neighbors3 = 9,
	Neighbors4 = 10,
	Neighbors5 = 11,
	Neighbors6 = 12,
	Neighbors7 = 13,
	Neighbors8 = 14
}

local boardSize = Vector3(107, 60)
local mineCount = boardSize.X * boardSize.Y * 0.15--500
local tiles = {}
local tilesOfInterest = {}
local tilesOfSafeInterest = {}
local activeMines
local boardTransform
local minesSpawned = 0
local tilesLeft = math.huge
local isAlive = true

function IsInBounds(x, y)
	return x >= 1 and x <= boardSize.X and y >= 1 and y <= boardSize.Y
end

function GetTile(x, y)
	if IsInBounds(x, y) then
		local row = tiles[y]
		
		if row then
			return row[x]
		end
	end
	
	return nil
end

function SetAppearance(tile, tileType)
	tile.Appearance.UVOffset = tileOffsets[tileType]
end

function UpdateTile(tile)
	if tile.IsOpen then
		if tile.IsMine then
			tile:SetAppearance(tile.IsBlown and TileTypes.BlownMine or TileTypes.Mine)
		else
			tile:SetAppearance(TileTypes.Neighbors0 + tile.Neighbors)
		end
	else
		if tile.IsFlagged then
			tile:SetAppearance(TileTypes.Flagged)
		elseif tile.IsPressing then
			tile:SetAppearance(TileTypes.Pressed)
		else
			tile:SetAppearance(TileTypes.Unknown)
		end
	end
end

function Reset(tile)
	tile.IsMine = false
	tile.IsOpen = false
	tile.IsBlown = false
	tile.IsPressing = false
	tile.IsFlagged = false
	tile.Neighbors = 0
	
	tile:UpdateTile()
end

function ComputeNeighbors(tile)
	if tile.IsMine then
		return
	end
	
	local neighbors = 0
	
	for x = -1, 1 do
		for y = -1, 1 do
			if not (x == 0 and y == 0) and IsInBounds(tile.X + x, tile.Y + y) then
				local neighbor = GetTile(tile.X + x, tile.Y + y)
				
				if neighbor.IsMine then
					neighbors = neighbors + 1
				end
			end
		end
	end
	
	tile.Neighbors = neighbors
	
	tile:UpdateTile()
end

function ComputeClosedNeighbors(tile)
	local closed = 0
	local flagged = 0
	
	for x = -1, 1 do
		for y = -1, 1 do
			if not (x == 0 and y == 0) and IsInBounds(tile.X + x, tile.Y + y) then
				local neighbor = GetTile(tile.X + x, tile.Y + y)
				
				if not neighbor.IsOpen and not neighbor.IsFlagged then
					closed = closed + 1
				end
				
				if neighbor.IsFlagged then
					flagged = flagged + 1
				end
			end
		end
	end
	
	return closed, flagged
end

local DeviceTransform = GameObject.DeviceTransform
local Appearance = GameObject.Appearance
local ScreenCanvas = GameObject.ScreenCanvas
local InputSubscriber = GameObject.InputSubscriber

function CreateTile(x, y)
	local row = tiles[y] or {}
	tiles[y] = row
	
	if row[x] then
		return row[x]
	end
	
	local transform = DeviceTransform()
	transform.Parent = boardTransform
	transform.Size = DeviceVector(0, 24, 0, 24)
	transform.Position = DeviceVector(0, (x - 1) * 24, 0, (y - 1) * 24)
	transform.AnchorPoint = DeviceVector(0, 0, 0, 0)

	local appearance = Appearance()
	appearance.Name = "Appearance"
	appearance.Parent = transform
	appearance.Color = RGBA(1, 1, 1,1)
	appearance.Texture = tileTexture
	appearance.TextureColor = RGBA(1, 1, 1, 1)
	appearance.UVScale = Vector3(1 / 7, -0.5)
	appearance.UVOffset = Vector3(0, 1)
	appearance.BlendTexture = false

	local canvas = ScreenCanvas()
	canvas.Appearance = appearance
	canvas.Name = "Canvas"
	canvas.Parent = transform
	
	local subscriber = InputSubscriber()
	subscriber.Parent = transform
	
	local tile = {
		Transform = transform,
		Appearance = appearance,
		X = x,
		Y = y,
		IsMine = false,
		IsOpen = false,
		IsBlown = false,
		IsPressing = false,
		IsFlagged = false,
		Neighbors = 0,
		SetAppearance = SetAppearance,
		UpdateTile = UpdateTile,
		Reset = Reset,
		ComputeNeighbors = ComputeNeighbors
	}
	
	tile:SetAppearance(TileTypes.Unknown)
	
	row[x] = tile
	
	return tile
end

function InitializeBoard()
	if boardTransform then
		boardTransform.Parent = nil
		boardTransform = nil
	end
	
	activeMines = nil
	isAlive = true
	tilesLeft = math.huge
	tiles = {}
	tilesOfInterest = {
		{}, {}, {}, 
		{}, {}, {}, 
		{}, {}
	}
	tilesOfSafeInterest = {
		{}, {}, {}, 
		{}, {}, {}, 
		{}, {}
	}
	
	boardTransform = GameObject.DeviceTransform()
	boardTransform.Parent = screen
	boardTransform.Size = DeviceVector(0, 24 * boardSize.X, 0, 24 * boardSize.Y)
	
	for x = 1, boardSize.X do
		for y = 1, boardSize.Y do
			CreateTile(x, y)
		end
	end
end

function NeighborsSelected(startX, startY, x, y)
	return x >= startX - 1 and x <= startX + 1 and y >= startY - 1 and y <= startY + 1
end

function GenerateMines(startX, startY)
	if activeMines then
		return
	end
	
	print("generated mines")
	
	activeMines = {}
	minesSpawned = 0
	
	for i = 1, mineCount do
		local placed = false
		
		for tries = 1, 15 do
			local mineX = math.random(1, boardSize.X)
			local mineY = math.random(1, boardSize.Y)
			
			if not (mineX == startX and mineY == startY) then
				local tile = GetTile(mineX, mineY)
				
				if not tile.IsMine and not NeighborsSelected(startX, startY, mineX, mineY) then
					tile.IsMine = true
					activeMines[#activeMines + 1] = tile
					
					placed = true
					
					for x = -1, 1 do
						for y = -1, 1 do
							if not (x == 0 and y == 0) and IsInBounds(tile.X + x, tile.Y + y) then
								local neighbor = GetTile(tile.X + x, tile.Y + y)
								
								if not neighbor.IsMine then
									neighbor:ComputeNeighbors()
								end
							end
						end
					end
					
					break
				end
			end
		end
		
		if not placed then
			break
		else
			minesSpawned = minesSpawned + 1
		end
	end
	
	tilesLeft = boardSize.X * boardSize.Y - minesSpawned
end

function RevealAllMines()
	print "died"
	
	for i, mine in pairs(activeMines) do
		mine.IsOpen = true
		mine:UpdateTile()
	end
end

local neighborOffsets = { Vector3(1, 0), Vector3(0, 1), Vector3(-1, 0), Vector3(0, -1), Vector3(-1, -1), Vector3(-1, 1), Vector3(1, -1), Vector3(1, 1) }

function RemoveFromGroup(tile, interestCategory, groupId, indexId)
	local currentGroup = tile[groupId]
	local index = tile[indexId]
	
	if currentGroup then
		local interestGroup = interestCategory[currentGroup]
		local lastIndex = #interestGroup
		local last = interestGroup[lastIndex]
		--print("b", interestGroup[index], interestGroup[lastIndex])
		
		if last == nil then print(#interestGroup, currentGroup, index) end
		
		last[indexId] = index
		interestGroup[index] = last
		interestGroup[lastIndex] = nil
		
		tile[indexId] = nil
		tile[groupId] = nil
		--print("a", interestGroup[index], interestGroup[lastIndex])
	end
end

function AddToGroup(tile, group, interestCategory, groupId, indexId)
	if tile.IsOpen and tile[groupId] ~= group and group > 0 then
		local interestGroup = interestCategory[group]
		local index = #interestGroup + 1
		
		--print("b", #interestGroup)
		interestGroup[index] = tile
		tile[groupId] = group
		tile[indexId] = index
		--print("a", #interestGroup)
	end
end

function UpdateGroup(tile, group, interestCategory, groupId, indexId)
	--print(tile.Neighbors, tile.X, tile.Y, group)
	--print("bg", tile[groupId], tile[indexId])
	if (group == 0 or not tile[groupId]) and group ~= tile[groupId] then
		RemoveFromGroup(tile, interestCategory, groupId, indexId)
	end
	
	if group > 0 and group ~= tile[groupId] then
		AddToGroup(tile, group, interestCategory, groupId, indexId)
	end
	--print("ag", tile[groupId], tile[indexId])
end

function GetScore(tile)
	local closed, flagged = ComputeClosedNeighbors(tile)
	local remaining = (closed - (tile.Neighbors - flagged))
	
	if closed == 0 then remaining = -1 end
	
	return remaining + 1, closed, flagged, tile.Neighbors
end

function LookAtTile(tile)
	if not tile.IsOpen or tile.Neighbors == 0 then
		UpdateGroup(tile, 0, tilesOfInterest, "InterestGroup", "InterestGroupIndex")
		
		return
	end
	
	local closed, flagged = ComputeClosedNeighbors(tile)
	local remaining = (closed - (tile.Neighbors - flagged))
	
	if closed == 0 then remaining = -1 end
	
	UpdateGroup(tile, remaining + 1, tilesOfInterest, "InterestGroup", "InterestGroupIndex")
	
	
	if tile.Neighbors > 0 and tile.Neighbors == flagged then
		if closed > 0  then
			UpdateGroup(tile, 1, tilesOfSafeInterest, "SafeInterestGroup", "SafeInterestGroupIndex")
		else
			UpdateGroup(tile, 0, tilesOfSafeInterest, "SafeInterestGroup", "SafeInterestGroupIndex")
		end
	end
end

local lookAtNext = {}

function ProcessLookingAt()
	print("looking at", #lookAtNext)
	for i,v in pairs(lookAtNext) do
		LookAtTile(v)
	end
	
	lookAtNext = {}
end

function LookAtNext(tile)
	lookAtNext[#lookAtNext + 1] = tile
end

function TileWasClicked(tile)
	for x = -1, 1 do
		for y = -1, 1 do
			if IsInBounds(tile.X + x, tile.Y + y) then
				local neighbor = GetTile(tile.X + x, tile.Y + y)
				
				LookAtNext(neighbor)
			end
		end
	end
end

function FindUnopenedNeighbor(tile)
	for x = -1, 1 do
		for y = -1, 1 do
			if IsInBounds(tile.X + x, tile.Y + y) then
				local neighbor = GetTile(tile.X + x, tile.Y + y)
				
				if not neighbor.IsOpen and not neighbor.IsFlagged then
					return neighbor
				end
			end
		end
	end
end

function RevealTilesAt(x, y)
	GenerateMines(x, y)
	
	local tile = GetTile(x, y)
	
	if tile.IsMine then
		tile.IsBlown = true
		isAlive = false
		
		RevealAllMines()
		
		return
	end
	
	local wasOpen = tile.IsOpen
	
	tile.IsOpen = true
	tile:UpdateTile()
	
	tilesLeft = tilesLeft - 1
	
	TileWasClicked(tile)
	
	if tile.Neighbors == 0 then
		local openNext = { tile }
		local count = 1
		
		while count > 0 do
			local current = openNext[count]
			
			openNext[count] = nil
			count = count - 1
			
			for i, offset in pairs(neighborOffsets) do
				local nextTile = GetTile(current.X + offset.X, current.Y + offset.Y)
				
				if nextTile and not nextTile.IsOpen then
					nextTile.IsOpen = true
					nextTile:UpdateTile()
					
					tilesLeft = tilesLeft - 1
					
					if nextTile.Neighbors == 0 then
						count = count + 1
						openNext[count] = nextTile
					else
						LookAtNext(nextTile)
					end
				end
			end
		end
	end
end

print "initializing board"

InitializeBoard()

print"done"

-- Add a script for controlling the camera in free cam mode
local freeCamSource = GameObject.LuaSource()
freeCamSource.Name = "FreeCamSource"
freeCamSource:LoadSource("./assets/scripts/freeCameraController.lua")

local freeCamScript = GameObject.LuaScript()
freeCamScript.Name = "FreeCamScript"
freeCamScript:SetSource(freeCamSource)
freeCamScript.Parent = camera

freeCamSource.Parent = freeCamScript

freeCamScript:Run()

-- Create some example objects in the scene
local defaultMaterial = GameObject.Material()
defaultMaterial.Shininess = 75
defaultMaterial.Diffuse = RGBA(0.5, 0.5, 0.5, 0)
defaultMaterial.Specular = RGBA(0.5, 0.5, 0.5, 0)
defaultMaterial.Ambient = RGBA(0.5, 0.5, 0.5, 0)
defaultMaterial.Emission = RGBA(0, 0, 0, 0)
defaultMaterial.Parent = level

function CreateObject(scene, meshAsset, material)
	if not meshAsset then
		print("CreateObject called with no mesh asset, defaulting to Core.Square")
	end
	if not material then
		print("CreateObject called with no material, defaulting to gray diffuse")
	end
	
	-- Many objects are built using transformation hierarchies. They search through their parents to find a Transform to inherit from.
	local transform = GameObject.Transform()
	
	--[[
		Models can be created that reference a material and mesh asset.
		The mesh asset is separate so it will only be created once and can be used across multiple objects.
		All 3D object rendering is tied to these models.
	]]
	local model = GameObject.Model()
	model.Parent = transform
	model.Asset = meshAsset or Engine.CoreMeshes.CoreCube
	model.MaterialProperties = material or defaultMaterial
	
	-- Register the model to the scene for rendering
	scene:AddObject(model)

	return transform
end

local objectsCreated = 0

for name in pairs(assets.meshes) do
	local object = CreateObject(scene, meshes[name])
	object.Transformation = Matrix3.EulerAnglesYawRotation(math.pi * objectsCreated / 5, 0, 0) * Matrix3(0, 0, 10)
	object.Parent = simulation
	object.Name = name
	
	print("Created", name)

	objectsCreated = objectsCreated + 1
end

local mouseLeft = Engine.GameWindow.UserInput:GetInput(Enum.InputCode.MouseLeft)
local mouseRight = Engine.GameWindow.UserInput:GetInput(Enum.InputCode.MouseRight)
local enterKey = Engine.GameWindow.UserInput:GetInput(Enum.InputCode.Enter)
local homeKey = Engine.GameWindow.UserInput:GetInput(Enum.InputCode.Home)
local endKey = Engine.GameWindow.UserInput:GetInput(Enum.InputCode.End)
local focused

local changedLeft = false
local changedRight = false
local lastLeft = false
local lastRight = false

math.randomseed(os.clock())

while true do
	wait()
	
	changedLeft = mouseLeft:GetState() ~= lastLeft
	lastLeft = mouseLeft:GetState()
	
	changedRight = mouseRight:GetState() ~= lastRight
	lastRight = mouseRight:GetState()
	
	local tileSelected = input:GetFocus(Enum.BoundDevice.Mouse1)
	local tile
	
	if isAlive and tilesLeft > 0 and tileSelected then
		local position = tileSelected.Parent.Position
		tile = GetTile(position.X.Offset / 24 + 1, position.Y.Offset / 24 + 1)
		
		if not tile.IsOpen then
			if not tile.IsFlagged and mouseLeft:GetState() and changedLeft then
				focused = tile
				
				focused.IsPressing = true
				focused:UpdateTile()
			end
			
			if mouseRight:GetState() and changedRight then
				tile.IsFlagged = not tile.IsFlagged
				tile:UpdateTile()
				
				if tile.IsFlagged then
					TileWasClicked(tile)
					ProcessLookingAt()
				end
			end
		end
	end
	
	if not mouseLeft:GetState() and focused then
		if changedLeft and focused == tile then
			RevealTilesAt(focused.X, focused.Y)
			ProcessLookingAt()
		end
		
		focused.IsPressing = false
		focused:UpdateTile()
		
		focused = nil
	end
	if endKey:GetState() and endKey:GetStateChanged() and tile then
		print(tile.X, tile.Y, GetScore(tile))
	end
	
	if homeKey:GetState()then-- and homeKey:GetStateChanged() then
		if #tilesOfInterest[1] > 0 then
			--print("bc", tilesOfInterest[1][1].X, tilesOfInterest[1][1].Y, tilesOfInterest[1][1].Neighbors, GetScore(tilesOfInterest[1][1]))
			local tile = FindUnopenedNeighbor(tilesOfInterest[1][1])
			if tile then
				tile.IsFlagged = true
				tile.IsPressing = false
				tile:UpdateTile()
				
				print("flagging", tile.X, tile.Y)
				
				TileWasClicked(tile)
				ProcessLookingAt()
				if tilesOfInterest[1][1] then
					--print("ac", tilesOfInterest[1][1].X, tilesOfInterest[1][1].Y, tilesOfInterest[1][1].Neighbors)
				else
					print("out of prio 1 tiles")
				end
			else
				print("ac", tilesOfInterest[1][1].X, tilesOfInterest[1][1].Y, GetScore(tilesOfInterest[1][1]))
				TileWasClicked(tilesOfInterest[1][1])
				ProcessLookingAt()
				local category = tilesOfInterest[1]
				print(#category)
				for i,v in ipairs(category) do
					local score, closed = GetScore(v)
					
					if score == 0 then
						category[i] = category[#category]
						category[i].InterestGroupIndex = i
						category[#category] = nil
						
						v.InterestGroup = nil
						v.InterestGroupIndex = nil
						
						print("removed at", i, #category)
					end
					print(score, closed)
					print(i, "|", v.X, v.Y, v.Neighbors, GetScore(v))
				end
				print"NIL TILE"
			end
		elseif #tilesOfSafeInterest[1] > 0 then
			local tile = FindUnopenedNeighbor(tilesOfSafeInterest[1][1])
			if tile then
				RevealTilesAt(tile.X, tile.Y)
				tile.IsPressing = false
				tile:UpdateTile()
				
				print("clicking", tile.X, tile.Y)
				
				TileWasClicked(tile)
				ProcessLookingAt()
				if tilesOfSafeInterest[1][1] then
					--print("ac", tilesOfInterest[1][1].X, tilesOfInterest[1][1].Y, tilesOfInterest[1][1].Neighbors)
				else
					print("out of prio 1 tiles")
				end
			else
				print"NIL TILE"
				print("tiles of interest:")
				local category = tilesOfSafeInterest[1]
				
				for i,v in ipairs(category) do
					local score, closed = GetScore(v)
					
					if closed == 0 then
						category[i] = category[#category]
						category[i].SafeInterestGroupIndex = i
						category[#category] = nil
						
						v.SafeInterestGroup = nil
						v.SafeInterestGroupIndex = nil
						
						print("removed at", i, #category)
					end
					print(score, closed)
					print(i, "|", v.X, v.Y, v.Neighbors, GetScore(v))
				end
			end
		else
			print("tiles of interest:")
			
			for i=1,8 do
				print(i, #tilesOfInterest[i])
			end
		end
	end
	
	if enterKey:GetState() and (not isAlive or tilesLeft == 0) then
		InitializeBoard()
	end
end