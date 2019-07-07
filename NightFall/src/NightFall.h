#pragma once

#include <NightFall/application/NightFallApplication.h>
#include <NightFall/logger/Logger.h>

// Event
#include <NightFall/event/Event.h>
#include <NightFall/event/EventHandler.h>
#include <NightFall/event/EventType.h>
#include <NightFall/event/EventListener.h>

// Events
#include <NightFall/event/events/KeyboardEvents.h>
#include <NightFall/event/events/MouseEvents.h>
#include <NightFall/event/events/WindowEvents.h>

// Utils
#include <NightFall/utils/DebugTools.h>
#include <NightFall/utils/Assert.h>

// Datatypes

// Window
#include <NightFall/application/Window.h>

// Input
#include <NightFall/application/Input.h>
#include <NightFall/application/KeyCodes.h>
#include <NightFall/application/MouseCodes.h>

// ImGui
#include <imgui.h>

// Layers
#include <NightFall/layers/Layer.h>
#include <NightFall/layers/LayerStack.h>
#include <NightFall/layers/layers/ImGuiLayer.h>

// Rendering
#include <NightFall/rendering/Buffer.h>
#include <NightFall/rendering/GraphicsContext.h>
#include <NightFall/rendering/RenderCommand.h>
#include <NightFall/rendering/Renderer.h>
#include <NightFall/rendering/RendererAPI.h>
#include <NightFall/rendering/Shader.h>
#include <NightFall/rendering/VertexArray.h>
	// Camera
	#include <NightFall/rendering/Camera.h>