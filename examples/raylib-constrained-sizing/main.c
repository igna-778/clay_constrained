#define CLAY_IMPLEMENTATION
#include "../../clay.h"
#include "../../renderers/raylib/clay_renderer_raylib.c"

const uint32_t FONT_ID_BODY_24 = 0;
const uint32_t FONT_ID_BODY_16 = 1;
#define COLOR_ORANGE (Clay_Color) {225, 138, 50, 255}
#define COLOR_BLUE (Clay_Color) {111, 173, 162, 255}

Texture2D profilePicture;
#define RAYLIB_VECTOR2_TO_CLAY_VECTOR2(vector) (Clay_Vector2) { .x = vector.x, .y = vector.y }

Clay_String profileText = CLAY_STRING_CONST("Profile Page one two three four five six seven eight nine ten eleven twelve thirteen fourteen fifteen");
Clay_TextElementConfig headerTextConfig = { .fontId = 1, .letterSpacing = 5, .fontSize = 16, .textColor = {0,0,0,255} };

void HandleHeaderButtonInteraction(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        // Do some click handling
    }
}

Clay_ElementDeclaration HeaderButtonStyle(bool hovered) {
    return (Clay_ElementDeclaration) {
        .layout = {.padding = {16, 16, 8, 8}},
        .backgroundColor = hovered ? COLOR_ORANGE : COLOR_BLUE,
    };
}

// Examples of re-usable "Components"
void RenderHeaderButton(Clay_String text) {
    CLAY(HeaderButtonStyle(Clay_Hovered())) {
        CLAY_TEXT(text, CLAY_TEXT_CONFIG(headerTextConfig));
    }
}

Clay_LayoutConfig dropdownTextItemLayout = { .padding = {8, 8, 4, 4} };
Clay_TextElementConfig dropdownTextElementConfig = { .fontSize = 24, .textColor = {255,255,255,255} };

void RenderDropdownTextItem(int index) {
    CLAY({ .layout = dropdownTextItemLayout, .backgroundColor = {180, 180, 180, 255} }) {
        CLAY_TEXT(CLAY_STRING("I'm a text field in a scroll container."), &dropdownTextElementConfig);
    }
}

float ConstrainedHeight(float width) {
    float x = width/2;
    if (x >= 150) {
        return 20;
    }
    return 170 - x;
}

float ConstrainedWidth(float height) {
    float x = height/2;
    if (x >= 150) {
        return 20;
    }
    return 170 - x;
}
const float maxWidth = 500;
float width = maxWidth;
bool widthGrows = false;
const float maxHeight = 500;
float height = maxHeight;
bool heightGrows = false;
float speed = 50;

Clay_RenderCommandArray CreateLayout(void) {
    float deltaTime = GetFrameTime();
    widthGrows = widthGrows ? width < maxWidth :  width < 40;
    heightGrows = heightGrows ? height < maxHeight :  height < 40;
    width = widthGrows ? width + deltaTime * speed : width - deltaTime * speed;
    height = heightGrows ? height + deltaTime * speed : height - deltaTime * speed;

    Clay_BeginLayout();
    CLAY({ .id = CLAY_ID("OuterContainer"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) }, .padding = { 100, 100, 100, 100 }, .childGap = 16 }, .backgroundColor = {200, 200, 200, 255} }) {
        CLAY({ .id = CLAY_ID("OuterInnerContainer"), .layout = { .sizing = { .width = CLAY_SIZING_FIXED(1000), .height = CLAY_SIZING_FIXED(height) }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {170, 170, 170, 255} }) {
            //CLAY_SIZING_CONSTRAINED( .min_function = &ConstrainedHeight, .max = 110 )
            CLAY({ .id = CLAY_ID("Fix Ref"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(100), .height = CLAY_SIZING_GROW(0) }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {100, 200, 200, 255} }) {}
            CLAY({ .id = CLAY_ID("fit"), .layout = { .sizing = { .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {200, 0, 0, 255} }) {
                CLAY({ .id = CLAY_ID("Constrained"), .layout = { .sizing = { .width = CLAY_SIZING_CONSTRAINED( .min_function = &ConstrainedWidth, .max = 115 ), .height = CLAY_SIZING_FIT(.min = 20 , .max = 242) }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {100, 200, 100, 255} }) {}
                CLAY({ .id = CLAY_ID("Constrained22"), .layout = { .sizing = { .width = CLAY_SIZING_CONSTRAINED( .min_function = &ConstrainedWidth, .max = 115 ), .height = CLAY_SIZING_FIT(.min = 20 , .max = 242) }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {100, 200, 100, 255} }) {}
            }
        }
    }
        CLAY({ .id = CLAY_ID("OuterContainer2"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) }, .padding = { 100, 100, 100, 100 }, .childGap = 16 }, .backgroundColor = {200, 200, 200, 255} }) {
        CLAY({ .id = CLAY_ID("OuterInnerContainer2"), .layout = { .sizing = { .width = CLAY_SIZING_FIXED(width), .height = CLAY_SIZING_FIXED(500) }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {170, 170, 170, 255} }) {
            //CLAY_SIZING_CONSTRAINED( .min_function = &ConstrainedHeight, .max = 110 )
            CLAY({ .id = CLAY_ID("Fix Ref2"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(100), .height = CLAY_SIZING_GROW(0) }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {100, 200, 200, 255} }) {}
            CLAY({ .id = CLAY_ID("Constrained 6"), .layout = { .sizing = { .width = CLAY_SIZING_CONSTRAINED( .min_function = &ConstrainedWidth, .max = 115 ), .height = CLAY_SIZING_FIT(.min = 20 , .max = 242) }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {100, 200, 100, 255} }) {}
            CLAY({ .id = CLAY_ID("fit2"), .layout = { .sizing = { .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {200, 0, 0, 255} }) {
                CLAY({ .id = CLAY_ID("Constrained 7"), .layout = { .sizing = { .width = CLAY_SIZING_FIT(.min = 20 , .max = 242), .height = CLAY_SIZING_CONSTRAINED( .min_function = &ConstrainedHeight, .max = 115 ) }, .padding = { 16, 16, 16, 16 }, .childGap = 16 }, .backgroundColor = {100, 100, 200, 255} }) {}
            }
        }
    }
    return Clay_EndLayout();
}

typedef struct
{
    Clay_Vector2 clickOrigin;
    Clay_Vector2 positionOrigin;
    bool mouseDown;
} ScrollbarData;

ScrollbarData scrollbarData = {0};

bool debugEnabled = false;

void UpdateDrawFrame(Font* fonts)
{
    Vector2 mouseWheelDelta = GetMouseWheelMoveV();
    float mouseWheelX = mouseWheelDelta.x;
    float mouseWheelY = mouseWheelDelta.y;

    if (IsKeyPressed(KEY_D)) {
        debugEnabled = !debugEnabled;
        Clay_SetDebugModeEnabled(debugEnabled);
    }
    //----------------------------------------------------------------------------------
    // Handle scroll containers
    Clay_Vector2 mousePosition = RAYLIB_VECTOR2_TO_CLAY_VECTOR2(GetMousePosition());
    Clay_SetPointerState(mousePosition, IsMouseButtonDown(0) && !scrollbarData.mouseDown);
    Clay_SetLayoutDimensions((Clay_Dimensions) { (float)GetScreenWidth(), (float)GetScreenHeight() });
    if (!IsMouseButtonDown(0)) {
        scrollbarData.mouseDown = false;
    }

    if (IsMouseButtonDown(0) && !scrollbarData.mouseDown && Clay_PointerOver(Clay_GetElementId(CLAY_STRING("ScrollBar")))) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("MainContent")));
        scrollbarData.clickOrigin = mousePosition;
        scrollbarData.positionOrigin = *scrollContainerData.scrollPosition;
        scrollbarData.mouseDown = true;
    } else if (scrollbarData.mouseDown) {
        Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("MainContent")));
        if (scrollContainerData.contentDimensions.height > 0) {
            Clay_Vector2 ratio = (Clay_Vector2) {
                scrollContainerData.contentDimensions.width / scrollContainerData.scrollContainerDimensions.width,
                scrollContainerData.contentDimensions.height / scrollContainerData.scrollContainerDimensions.height,
            };
            if (scrollContainerData.config.vertical) {
                scrollContainerData.scrollPosition->y = scrollbarData.positionOrigin.y + (scrollbarData.clickOrigin.y - mousePosition.y) * ratio.y;
            }
            if (scrollContainerData.config.horizontal) {
                scrollContainerData.scrollPosition->x = scrollbarData.positionOrigin.x + (scrollbarData.clickOrigin.x - mousePosition.x) * ratio.x;
            }
        }
    }

    Clay_UpdateScrollContainers(true, (Clay_Vector2) {mouseWheelX, mouseWheelY}, GetFrameTime());
    // Generate the auto layout for rendering
    double currentTime = GetTime();
    Clay_RenderCommandArray renderCommands = CreateLayout();
    printf("layout time: %f microseconds\n", (GetTime() - currentTime) * 1000 * 1000);
    // RENDERING ---------------------------------
//    currentTime = GetTime();
    BeginDrawing();
    ClearBackground(BLACK);
    Clay_Raylib_Render(renderCommands, fonts);
    EndDrawing();
//    printf("render time: %f ms\n", (GetTime() - currentTime) * 1000);

    //----------------------------------------------------------------------------------
}

bool reinitializeClay = false;

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
    if (errorData.errorType == CLAY_ERROR_TYPE_ELEMENTS_CAPACITY_EXCEEDED) {
        reinitializeClay = true;
        Clay_SetMaxElementCount(Clay_GetMaxElementCount() * 2);
    } else if (errorData.errorType == CLAY_ERROR_TYPE_TEXT_MEASUREMENT_CAPACITY_EXCEEDED) {
        reinitializeClay = true;
        Clay_SetMaxMeasureTextCacheWordCount(Clay_GetMaxMeasureTextCacheWordCount() * 2);
    }
}

int main(void) {
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(clayMemory, (Clay_Dimensions) { (float)GetScreenWidth(), (float)GetScreenHeight() }, (Clay_ErrorHandler) { HandleClayErrors, 0 });
    Clay_Raylib_Initialize(1024, 768, "Clay - Raylib Renderer Example", FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    profilePicture = LoadTexture("resources/profile-picture.png");

    Font fonts[2];
    fonts[FONT_ID_BODY_24] = LoadFontEx("resources/Roboto-Regular.ttf", 48, 0, 400);
	SetTextureFilter(fonts[FONT_ID_BODY_24].texture, TEXTURE_FILTER_BILINEAR);
    fonts[FONT_ID_BODY_16] = LoadFontEx("resources/Roboto-Regular.ttf", 32, 0, 400);
    SetTextureFilter(fonts[FONT_ID_BODY_16].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (reinitializeClay) {
            Clay_SetMaxElementCount(8192);
            totalMemorySize = Clay_MinMemorySize();
            clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
            Clay_Initialize(clayMemory, (Clay_Dimensions) { (float)GetScreenWidth(), (float)GetScreenHeight() }, (Clay_ErrorHandler) { HandleClayErrors, 0 });
            reinitializeClay = false;
        }
        UpdateDrawFrame(fonts);
    }
    Clay_Raylib_Close();
    return 0;
}
