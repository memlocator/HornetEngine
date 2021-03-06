local userInput = Engine.GameWindow.UserInput

local controller = {
	Bindings = {
		ForwardsKey = userInput:GetInput(Enum.InputCode.W),
		BackwardsKey = userInput:GetInput(Enum.InputCode.S),
		LeftKey = userInput:GetInput(Enum.InputCode.A),
		RightKey = userInput:GetInput(Enum.InputCode.D),
		UpKey = userInput:GetInput(Enum.InputCode.E),
		DownKey = userInput:GetInput(Enum.InputCode.Q),
		FastKey = userInput:GetInput(Enum.InputCode.Space),
		TurnKey = userInput:GetInput(Enum.InputCode.MouseRight),
		MovementInput = userInput:GetInput(Enum.InputCode.MousePosition)
	},
	Settings = {
		DefaultSpeed = 20,
		FastSpeed = 100
	},
	Camera = {
		AspectRatio = GameObject.FrameBuffer.WindowSize.Width / GameObject.FrameBuffer.WindowSize.Height,
		Size = 5 / 3,
		DefaultWidth = 0,
		DefaultHeight = 0,
		DefaultProjection = 1,
		DefaultNear = 0.1,
		DefaultFar = 10000
	}
}

controller.Camera.DefaultWidth = controller.Camera.AspectRatio * controller.Camera.Size
controller.Camera.DefaultHeight = controller.Camera.Size

local bindings = controller.Bindings
local settings = controller.Settings

local speed = controller.Settings.DefaultSpeed
local pitch = 0
local yaw = 0
local previousPosition = bindings.MovementInput:GetPosition()

coroutine.wrap(function()
	while true do
		local delta = wait()

		local camera = This:GetComponent("Camera")

		if camera then
			local x = 0
			local y = 0
			local z = 0
		
			if bindings.FastKey:GetState() then
				speed = settings.FastSpeed
			else
				speed = settings.DefaultSpeed
			end

			if bindings.ForwardsKey:GetState() then
				z = -delta * speed
			end

			if bindings.BackwardsKey:GetState() then
				z = delta * speed
			end
		
			if bindings.LeftKey:GetState() then
				x = -delta * speed
			end

			if bindings.RightKey:GetState() then
				x = delta * speed
			end

			if bindings.DownKey:GetState() then
				y = -delta * speed
			end
		
			if bindings.UpKey:GetState() then
				y = delta * speed
			end
			
			if bindings.TurnKey:GetState() then
				local currentPosition = bindings.MovementInput:GetPosition()
				local mouseDelta = currentPosition - previousPosition

				yaw = (yaw - mouseDelta.X * delta * 0.1 + 2 * math.pi) % (2 * math.pi)
				pitch = math.min(math.max(pitch - mouseDelta.Y * delta * 0.1, -math.pi / 2), math.pi / 2)

				Engine.GameWindow:SetMousePosition(previousPosition)
			else
				previousPosition = bindings.MovementInput:GetPosition()
			end

			local transform = camera:GetTransformation() * Matrix4(x, y, z)
			local rotation = (Matrix4.YawRotation(yaw) * Matrix4.PitchRotation(pitch)):TransformedAround(transform:Translation())

			camera:SetTransformation(rotation * Matrix4(transform:Translation()))
		end
	end
end)()

return controller