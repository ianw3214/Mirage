#include "imgui_wrapper.hpp"

#include <SDL2/SDL_syswm.h> 
#include "engine.hpp"

#include "imgui.h"
#include "platform/openGL/imgui_impl_opengl3.h"

static bool         g_MousePressed[3] = { false, false, false };
static SDL_Cursor*  g_MouseCursors[ImGuiMouseCursor_COUNT] = { 0 };
static char*        g_ClipboardTextData = NULL;

static const char* ImGui_ImplSDL2_GetClipboardText(void*) {
    if (g_ClipboardTextData)
        SDL_free(g_ClipboardTextData);
    g_ClipboardTextData = SDL_GetClipboardText();
    return g_ClipboardTextData;
}

static void ImGui_ImplSDL2_SetClipboardText(void*, const char* text) {
    SDL_SetClipboardText(text);
}

ImGuiWrapper::ImGuiWrapper() {
    // Initialize member variables first
    g_ClipboardTextData = nullptr;
    g_window = Engine::getWindow();

    // Init ImGui
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
    io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
    io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
    io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
    io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
    io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
    io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
    io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
    io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
    io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
    io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
    io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
    io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
    io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
    io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;

    io.SetClipboardTextFn = ImGui_ImplSDL2_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplSDL2_GetClipboardText;
    io.ClipboardUserData = NULL;

    ImGui_ImplOpenGL3_Init("#version 400");

    g_MouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    g_MouseCursors[ImGuiMouseCursor_TextInput] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    g_MouseCursors[ImGuiMouseCursor_ResizeAll] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    g_MouseCursors[ImGuiMouseCursor_ResizeNS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    g_MouseCursors[ImGuiMouseCursor_ResizeEW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
    g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    g_MouseCursors[ImGuiMouseCursor_Hand] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

#ifdef _WIN32
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(g_window, &wmInfo);
    io.ImeWindowHandle = wmInfo.info.win.window;
#else
    (void)window;
#endif
}

ImGuiWrapper::~ImGuiWrapper() {

}

void ImGuiWrapper::render() {
    // TODO: (Ian) Fix these calculations
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(500, 500);
    io.DeltaTime = 1.0f / 60.f;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWrapper::onEvent(const SDL_Event& e) {
    ImGuiIO& io = ImGui::GetIO();
    switch(e.type) {
        case SDL_MOUSEWHEEL:        onMouseWheelEvent(e.wheel, io);         break;
        case SDL_MOUSEBUTTONDOWN:   onMousePressedEvent(e.button, io);      break;
        case SDL_TEXTINPUT:         onTextInputEvent(e.text, io);           break;
        case SDL_KEYDOWN:           onKeyDownEvent(e.key, io);              break;
        case SDL_KEYUP:             onKeyUpEvent(e.key, io);                break;
    }    
}

void ImGuiWrapper::onMouseWheelEvent(const SDL_MouseWheelEvent& e, ImGuiIO& io) {
    if (e.x > 0) io.MouseWheelH += 1;
    if (e.x < 0) io.MouseWheelH -= 1;
    if (e.y > 0) io.MouseWheel += 1;
    if (e.y < 0) io.MouseWheel -= 1;
}

void ImGuiWrapper::onMousePressedEvent(const SDL_MouseButtonEvent& e, ImGuiIO& io) {
    if (e.button == SDL_BUTTON_LEFT) g_MousePressed[0] = true;
    if (e.button == SDL_BUTTON_RIGHT) g_MousePressed[1] = true;
    if (e.button == SDL_BUTTON_MIDDLE) g_MousePressed[2] = true;
}

void ImGuiWrapper::onTextInputEvent(const SDL_TextInputEvent& e, ImGuiIO& io) {
    io.AddInputCharactersUTF8(e.text);
}

void ImGuiWrapper::onKeyDownEvent(const SDL_KeyboardEvent& e, ImGuiIO& io) {
    int key = e.keysym.scancode;
    IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
    io.KeysDown[key] = true;
    io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
    io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
    io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
    io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
}

void ImGuiWrapper::onKeyUpEvent(const SDL_KeyboardEvent& e, ImGuiIO& io) {
    int key = e.keysym.scancode;
    IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
    io.KeysDown[key] = true;
    io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
    io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
    io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
    io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
}
