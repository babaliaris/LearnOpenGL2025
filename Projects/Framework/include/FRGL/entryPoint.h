#pragma once

#ifdef FRGL_ENTRY_POINT
    int main(int argc, char **argv)
    {
        FRGL::Application *new_app = FRGL::CreateApplication();

        new_app->Run();

        delete new_app;

        return 0;
    }
#endif