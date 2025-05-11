#ifndef MAP_H
#define MAP_H

#include "cLDtk.h"
#include <math.h>


void CreateMap(const char* filePath){
    loadJSONFile("{\"jsonVersion\":\"\"}", filePath);
    importMapData();
}

void UpdateMap(void){

}

void DrawSprite(Texture2D texture, Rectangle sourceRec, Vector2 position,int flip, Color tint) 
{
    Rectangle destRec = { position.x, position.y, fabsf(sourceRec.width), fabsf(sourceRec.height) };
    Vector2 origin = { 0.0f, 0.0f };
    
    //flip=0;
    
    switch(flip){
        case 0 :
            //flipx =false; 
            //flipy = false;
            break;
        case 1 :
            //flipx = true; 
            //flipy = false;
            sourceRec.width *= -1;
            break;
        
        case 2 :
            //flipx = false; 
            //flipy = true;
            sourceRec.height *= -1;
            break;
        case 3 :
            //flipx = true; 
            //flipy = true;
            sourceRec.width *= -1;
            sourceRec.height *= -1;
            
            break;
            
    }
    
    

    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, tint);
  
}


void DrawTiles(struct layerInstances *layer,Texture2D texture,int offset,Color tint)
{
    
    for(int y=layer->autoTiles_data_ptr->count ;y-- > 0;){ 
            
        DrawSprite(
            texture,
            (Rectangle){(float)layer->autoTiles_data_ptr[y].SRCx,(float)layer->autoTiles_data_ptr[y].SRCy,offset,offset},
            (Vector2){(float)layer->autoTiles_data_ptr[y].x,(float)layer->autoTiles_data_ptr[y].y},
            layer->autoTiles_data_ptr[y].f,
            tint);
    }

} 

void RenderMap(Texture2D mapAtlas, struct levels* lvl_one, struct layerInstances* lvl_one_background, struct layerInstances* lvl_one_collisions){
    DrawTiles(lvl_one_background,mapAtlas,16,WHITE);
    DrawTiles(lvl_one_collisions,mapAtlas,16,WHITE);
}

void UnloadMap(void){
    freeMapData();
    
    json_value_free(schema);
    json_value_free(user_data);
}



#endif // MAP_H
