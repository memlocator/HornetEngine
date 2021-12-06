local stack = {}

local resolution = GameObject.FrameBuffer.WindowSize

local screen = GameObject("DeviceTransform")
screen.Size = DeviceVector(0, resolution.Width, 0, resolution.Height)
screen.Parent = Engine

local ui = GameObject("InterfaceDrawOperation")
ui.CurrentScreen = screen
ui.RenderAutomatically = true
ui.Parent = screen

local explorerTransform = GameObject("DeviceTransform")
explorerTransform.Size = DeviceVector(0.2, 0, 1, 0)
explorerTransform.Position = DeviceVector(0.8, 0, 0, 0)
explorerTransform.Parent = screen

local fonts = GameObject("Fonts")
fonts.Parent = Engine

local sans = GameObject("Font")
sans.Name = "Sans"
sans:Load("assets/fonts/Sans", "Sans")
sans.Parent = fonts

local renderedObjects = 0
local itemHeight = 20
local tabWidth = 20

function AllocateItem(name)
	renderedObjects = renderedObjects + 1
	
	local objectTransform, displayTransform
	local width = tabWidth * (#stack - 1)
	
	if explorerTransform:GetChildren() < renderedObjects then
		objectTransform = GameObject("DeviceTransform")
		objectTransform.Size = DeviceVector(1, 0, 0, itemHeight)
		objectTransform.Position = DeviceVector(0, 0, 0, (renderedObjects - 1) * itemHeight)
		objectTransform.Parent = explorerTransform
		
		local backgroundAppearance = GameObject("Appearance")
		backgroundAppearance.Parent = objectTransform
		backgroundAppearance.Color = RGBA(0, 0, 0, 0.5)

		local backgroundCanvas = GameObject("ScreenCanvas")
		backgroundCanvas.Appearance = backgroundAppearance
		backgroundCanvas.Parent = objectTransform
		
		displayTransform = GameObject("DeviceTransform")
		displayTransform.Parent = objectTransform
		displayTransform.Name = "DisplayTransform"
		
		local appearance = GameObject("Appearance")
		appearance.Parent = displayTransform
		appearance.Color = RGBA(1, 1, 1, 1)

		local canvas = GameObject("ScreenCanvas")
		canvas.Appearance = appearance
		canvas.Parent = displayTransform
		
		local splitterTransform = GameObject("DeviceTransform")
		splitterTransform.Parent = objectTransform
		splitterTransform.Size = DeviceVector(1, -20, 0, 2)
		splitterTransform.Position = DeviceVector(0, 10, 1, -1)
		
		local splitterAppearance = GameObject("Appearance")
		splitterAppearance.Parent = splitterTransform
		splitterAppearance.Color = RGBA(0.8, 0.8, 0.8, 0.4)

		local splitterCanvas = GameObject("ScreenCanvas")
		splitterCanvas.Appearance = splitterAppearance
		splitterCanvas.Parent = splitterTransform
		
		print("name: ", name)
		
		local text = GameObject.Text.Create(sans, canvas, "DisplayText", name)
		text.FontSize = DeviceAxis(0, 19)
	else
		objectTransform = explorerTransform:Get(renderedObjects - 1)
		
		displayTransform = objectTransform.DisplayTransform
	end
	
	displayTransform.Size = DeviceVector(1, -width, 1, 0)
	displayTransform.Position = DeviceVector(0, width, 0, 0)
end

function PushObject(object)
	if renderedObjects > 1000 or #stack > 1 then
		return
	end
	
	local item = {
		Object = object,
		Children = object:GetChildren(),
		CurrentChild = 1
	}
	
	print(("%s%s (%d)"):format(("   "):rep(#stack), object.Name, object:GetObjectID()))
	
	stack[#stack + 1] = item
	
	if object == screen then
		item.CurrentChild = 1 + item.Children
		
		return Advance()
	end
	
	AllocateItem(object.Name)
end

function Advance()
	if #stack == 0 then return end
	
	local top = stack[#stack]
	
	if top.CurrentChild > top.Children then
		stack[#stack] = nil
		
		return Advance()
	end
	
	PushObject(top.Object:Get(top.CurrentChild - 1))
	
	top.CurrentChild = top.CurrentChild + 1
end

PushObject(Engine)

while #stack > 0 do
	Advance()
end

for i = explorerTransform:GetChildren(), renderedObjects + 1, -1 do
	explorerTransform:Get(i - 1).Parent = nil
end