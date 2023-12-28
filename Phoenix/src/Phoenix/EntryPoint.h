#pragma once

#ifdef PN_PLATFORM_WINDOWS

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv) {
    Phoenix::Log::Init();
    PN_CORE_INFO("Welcome to the Phoenix Engine.");
    PN_CLIENT_TRACE("Sandbox started.");
    Phoenix::Application* app = Phoenix::CreateApplication();
    app->Run();
    delete app;
}

#endif // PN_PLATFORM_WINDOWS
