#include <raylib.h>
#include <raymath.h>

const int TileWidth = 8;
const int TileHeight = 8;


const int ScreenWidth= 960;
const int ScreenHeight = 540;

const int MAX_TEXTURES = 1;
typedef enum
{
    TEXTURE_TILEMAP = 0

}texture_assets;

const int WORLD_WIDHT = 20; // WORDL_WIDTH * TILE_WIDTH
const int WORLD_HEIGHT = 20;// WORLD_HEIGHT * TILE_HEIGHT

typedef struct 
{
    int x;
    int y;
}sTILE;

sTILE world[WORLD_WIDHT] [WORLD_HEIGHT];

Camera2D camera = {0}; 


Texture2D textures[MAX_TEXTURES];

void GameStartup()
{
    InitAudioDevice();

    Image image = LoadImage("assets/colored_tilemap_packed6.png"); 
    textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
    UnloadImage(image);

    for(int i = 0; i < WORLD_WIDHT;i++)
    {
        for(int j = 0; j < WORLD_HEIGHT;j++)
        {
            world[i][j] = sTILE
            {
                .x = i,
                .y = j
            };
        }
    }

    camera.target = Vector2{0,0};
    camera.offset = Vector2{(float) ScreenWidth / 2, (float) ScreenHeight / 2};
    camera.rotation = 0;
    camera.zoom = 3.0f;
}
void GameUpdate()
{
    float wheel = GetMouseWheelMove();
    if( wheel != 0 )
    {
        const float zoomIncrement = 0.125f;
        camera.zoom += zoomIncrement;
    }
    camera.target = (Vector2) {0,0};

}
void GameRenderer()
{

    BeginMode2D(camera);

    sTILE tile;
    int Texture_Index_x;
    int Texture_Index_y;

    for(int i = 0; i < WORLD_WIDHT;i++)
    {
        for(int j = 0; j < WORLD_HEIGHT; j++)
        {
            tile = world[i] [j];

            Texture_Index_x = 4;
            Texture_Index_y = 4;

            Rectangle source = {(float) Texture_Index_x * TileWidth,(float) Texture_Index_y * TileHeight,(float) TileWidth,(float) TileHeight};
            Rectangle dest = {(float) tile.x * TileWidth,(float) tile.y * TileHeight,(float) TileWidth,(float) TileHeight};
            Vector2 origin = {0, 0};
            
            DrawTexturePro(textures[TEXTURE_TILEMAP],source,dest,origin,0.0f,WHITE);
        }

    }

    EndMode2D();
}

 

void GameShutdown()
{
    for(int i = 0; i < MAX_TEXTURES; i++)
    {
        UnloadTexture(textures[i]);
    }
    CloseAudioDevice();
}




int main()
{

    InitWindow(ScreenWidth,ScreenHeight,"Window ");
    SetTargetFPS(60);
    GameStartup();
    

    
    
    while(!WindowShouldClose())
    {


        //update

      
        GameUpdate();
        //Draw 
        BeginDrawing();
        ClearBackground(GRAY);


        GameRenderer();
        EndDrawing();
        
    }

    GameShutdown();
    CloseWindow();
    return 0;

}