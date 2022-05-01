
import <iostream>;
import <forward_list>;
import <chrono>;
extern "C" {
#include <Windows.h>
}

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifdef near
#undef near
#endif

#ifdef far
#undef far
#endif

#include "Object.h"
#include "GameEngine.h"
#include "Graphics.h"
#include "Scene.h"
#include "FrameBase.h"
#include "InputProcessor.h"
#include "GlowingSceneOperation.h"
#include "Engine.h"
#include "GameWindow.h"
#include "LuaInput.h"
#include "LuaSource.h"
#include "LuaScript.h"
#include "VoxelTriangulation.h"
#include "EnginePackage.h"
#include "LuaPackage.h"
#include "NetworkingPackage.h"
#include "PhysicsPackage.h"
#include "TerrainPackage.h"
#include "GraphicsScenePackage.h"
#include "GraphicsCorePackage.h"
#include "GraphicsUIPackage.h"
#include "GraphicsRTPackage.h"
#include "GraphicsDebugPackage.h"
#include "GraphicsDataPackage.h"
#include "GraphicsOperationPackage.h"
#include "EditorPackage.h"
#include "Reflection/DebugPrintMeta.h"
#include "Reflection/LuaEnvironment.h"

// Add NoLua reflection tag
// Add Object::Clone(bool deep = true)

enum ab { c };

int main(int argc, char* argv[])
{
	Engine::Reflection::ReflectPackages<
		Engine::Reflection::EnginePackage,
		Engine::Reflection::LuaPackage,
		Engine::Reflection::NetworkingPackage,
		Engine::Reflection::PhysicsPackage,
		Engine::Reflection::TerrainPackage,
		Engine::Reflection::GraphicsScenePackage,
		Engine::Reflection::GraphicsCorePackage,
		Engine::Reflection::GraphicsUIPackage,
		Engine::Reflection::GraphicsRTPackage,
		Engine::Reflection::GraphicsDebugPackage,
		Engine::Reflection::GraphicsDataPackage,
		Engine::Reflection::GraphicsOperationPackage,
		Engine::Reflection::EditorPackage
	>();

  // Initialization
	try
	{
		Engine::InitializeEngine();
		Graphics::Initialize();

		Engine::Root()->Configure(argc, &argv[0]);
	}
	catch (std::string& error)
	{
		std::cout << error << std::endl;
		OutputDebugString(error.c_str());
		abort();
	}

  // Engine Start
	{
		Window& window = *Graphics::System->ActiveWindow;


		Engine::Lua::LuaEnvironment luaEnv;

		window.Update();

		std::shared_ptr<GraphicsEngine::GameWindow> gameWindow = Engine::Create<GraphicsEngine::GameWindow>();

		gameWindow->Configure(&window);
		gameWindow->SetParent(Engine::Root());

		Engine::Root()->SetPrimaryWindow(gameWindow);

		Engine::VoxelTriangulation::Initialize();

		{
			std::string path;

			if (argc > 1)
				path = argv[1];
			else
				path = "./main.lua";

			std::shared_ptr<Engine::LuaSource> source = Engine::Create<Engine::LuaSource>();
			source->Name = "GameScriptSource";
			source->LoadSource(path);
			
			std::shared_ptr<Engine::LuaScript> script = Engine::Create<Engine::LuaScript>();
			script->Name = "GameScript";
			script->SetSource(source);
			script->SetParent(Engine::Root());

			source->SetParent(script);

			script->Run();
		}

		{
			auto start = std::chrono::high_resolution_clock::now();

			luaEnv.UpdateLua(luaEnv.GetEnv(), 0);

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

			float durationMS = (float(duration.count()) / 1e6f);

			std::cout << "load time: " << durationMS << " miliseconds" << std::endl;
		}

		// Game Loop
		while (!window.IsClosed())
		{
			float delta = window.Update();

			if (delta > 1.0f / 30)
				delta = 1.0f / 30;

			TaskScheduler::Update(delta);

			std::shared_ptr<Engine::Object>(Engine::Root())->Update(delta);

			luaEnv.UpdateLua(luaEnv.GetEnv(), delta);

			GraphicsEngine::RenderOperation::RenderOperations();

			window.Swap();
		}
	}

  // Shutdown
	try
	{
		Engine::CleanEngine();

		Graphics::Clean();
	}
	catch (std::string& error)
	{
		std::cout << error << std::endl;
		OutputDebugString(error.c_str());
		abort();
	}

	return 0;
}
