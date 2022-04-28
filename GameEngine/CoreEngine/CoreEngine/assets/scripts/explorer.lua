local stack = {}

local resolution = GameObject.FrameBuffer.WindowSize

local inputContext = GameObject.InputContext()
inputContext.Parent = Engine
inputContext.InputSource = Engine.GameWindow.UserInput

local screen = GameObject.DeviceTransform()
screen.Size = DeviceVector(0, resolution.Width, 0, resolution.Height)
screen.Parent = inputContext

inputContext.Device = screen

local ui = GameObject.InterfaceDrawOperation()
ui.CurrentScreen = screen
ui.RenderAutomatically = true
ui.Parent = screen

local explorerTransform = GameObject.DeviceTransform()
explorerTransform.Size = DeviceVector(0.2, 0, 1, 0)
explorerTransform.Position = DeviceVector(0.8, 0, 0, 0)
explorerTransform.Parent = screen

local explorerFrameTransform = GameObject.DeviceTransform()
explorerFrameTransform.Size = DeviceVector(1, -20, 1, 0)
explorerFrameTransform.Position = DeviceVector(0, 0, 0, 0)
explorerFrameTransform.Parent = explorerTransform

local barAppearance = GameObject.Appearance()
barAppearance.Parent = explorerTransform
barAppearance.Color = RGBA(1, 1, 1, 1)

local backgroundAppearance = GameObject.Appearance()
backgroundAppearance.Parent = explorerTransform
backgroundAppearance.Color = RGBA(0, 0, 0, 0.5)

local splitterAppearance = GameObject.Appearance()
splitterAppearance.Parent = explorerTransform
splitterAppearance.Color = RGBA(0.8, 0.8, 0.8, 0.4)

local explorerScrollBar = GameObject.ScrollBar()
explorerScrollBar.FrameTransform.Size = DeviceVector(0, 20, 1, 0)
explorerScrollBar.FrameTransform.Position = DeviceVector(1, -20, 0, 0)
explorerScrollBar.FrameCanvas.Appearance = backgroundAppearance
explorerScrollBar.BarCanvas.Appearance = barAppearance
explorerScrollBar.Parent = explorerTransform

function MakeBorder(size, position)
	local borderTransform = GameObject.DeviceTransform()
	borderTransform.Size = size
	borderTransform.Position = position
	borderTransform.Parent = explorerScrollBar.FrameTransform
	
	local borderCanvas = GameObject.ScreenCanvas()
	borderCanvas.Parent = borderTransform
	borderCanvas.Appearance = barAppearance
end

MakeBorder(DeviceVector(1, 0, 0, 1), DeviceVector(0, 0, 0, 0))
MakeBorder(DeviceVector(1, 0, 0, 1), DeviceVector(0, 0, 1, -1))
MakeBorder(DeviceVector(0, 1, 1, 0), DeviceVector(0, 0, 0, 0))
MakeBorder(DeviceVector(0, 1, 1, 0), DeviceVector(1, -1, 0, 0))

local fonts = GameObject.Fonts()
fonts.Parent = Engine

local sans = GameObject.Font()
sans.Name = "Sans"
sans:Load("assets/fonts/Sans", "Sans")
sans.Parent = fonts

local explorerDisplay = GameObject.ExplorerDisplaySettings()

local renderedObjects = 0
local itemHeight = 20
local tabWidth = 20
local maxItems = math.floor(resolution.Height / itemHeight) + 1
local scrollSpeed = 0.01
local scrollPercent = 0

function AllocateItem(item)
	renderedObjects = renderedObjects + 1
	
	local objectTransform, displayTransform
	local width = tabWidth * item.HierarchyDepth
	
	if explorerFrameTransform:GetChildren() < renderedObjects then
		objectTransform = GameObject.DeviceTransform()
		objectTransform.Size = DeviceVector(1, 0, 0, itemHeight)
		objectTransform.Position = DeviceVector(0, 0, 0, (renderedObjects - 1) * itemHeight)
		objectTransform.Parent = explorerFrameTransform
		
		local backgroundCanvas = GameObject.ScreenCanvas()
		backgroundCanvas.Appearance = backgroundAppearance
		backgroundCanvas.Parent = objectTransform
		
		displayTransform = GameObject.DeviceTransform()
		displayTransform.Parent = objectTransform
		displayTransform.Name = "DisplayTransform"
		
		local canvas = GameObject.ScreenCanvas()
		canvas.Parent = displayTransform
		canvas.Name = "TextCanvas"
		
		local splitterTransform = GameObject.DeviceTransform()
		splitterTransform.Parent = objectTransform
		splitterTransform.Size = DeviceVector(1, -20, 0, 2)
		splitterTransform.Position = DeviceVector(0, 10, 1, -1)

		local splitterCanvas = GameObject.ScreenCanvas()
		splitterCanvas.Appearance = splitterAppearance
		splitterCanvas.Parent = splitterTransform
		
		local text = GameObject.Text.Create(sans, canvas, "DisplayText", item.FocusedItem.Name)
		text.FontSize = DeviceAxis(0, 19)
	else
		objectTransform = explorerFrameTransform:Get(renderedObjects - 1)
		
		displayTransform = objectTransform.DisplayTransform
		
		displayTransform.TextCanvas.DisplayText:SetText(item.FocusedItem.Name)
	end
	
	displayTransform.Size = DeviceVector(1, -width, 1, 0)
	displayTransform.Position = DeviceVector(0, width, 0, 0)
end

local userInput = Engine.GameWindow.UserInput
local mouseWheel = userInput:GetInput(Enum.InputCode.MouseWheel)

coroutine.wrap(function()
	while true do
		local delta = wait()
		
		local wheelChange = -mouseWheel:GetPosition().Y
		
		--explorerScrollBar.BarPercent = math.max(0, math.min(1, explorerScrollBar.BarPercent + wheelChange * scrollSpeed))

		renderedObjects = 0
		
		explorerDisplay:UpdateHierarchy()

		for i = 1, math.min(maxItems, explorerDisplay:GetHierarchyItems()) do
			AllocateItem(explorerDisplay:GetObjectInHierarchy(maxItems, explorerScrollBar.BarPercent, i - 1))
		end
	end
end)()