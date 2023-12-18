#pragma once

#ifdef PN_PLATFORM_WINDOWS

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv) {
    printf("Welcome to the Phoenix Engine.\n");
    auto app = Phoenix::CreateApplication();
    app->Run();
    delete app;
}

#endif // PN_PLATFORM_WINDOWS
