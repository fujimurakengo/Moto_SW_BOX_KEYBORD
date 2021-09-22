#include "Keyboard.h"

//スイッチIOの番号指定
#define PASSING 7
#define HI_BEAM 5

#define TURN_R  6
#define TURN_L  4
#define HORN    3


#define PASSING_key 0
#define HI_BEAM_key 1
#define TURN_R_key  2
#define TURN_L_key  3
#define HORN_key    4//KEY_RETURN

void key_send_bunki(void);



//HI_LOW_beamモード切り替えのenum型
typedef  enum{
  VSCODE_MODE= 0,
  CS_PLISE_MODE
}mode_t;
//方向指示器切り替えのenum型
typedef  enum{
  CENTER= 0,
  LEFT_MODE,
  RIGH_MODE
}indicator_t;


//グローバル変数設定
mode_t mode = VSCODE_MODE;
indicator_t indicator=CENTER;


void setup() {
  // put your setup code here, to run once:


  pinMode(PASSING, INPUT_PULLUP);
  pinMode(HI_BEAM, INPUT_PULLUP);
  pinMode(TURN_R, INPUT_PULLUP);
  pinMode(TURN_L, INPUT_PULLUP);
  pinMode(HORN, INPUT_PULLUP);
  //なくてもええらしいな
  Keyboard.begin();
  Keyboard.releaseAll();
}

void loop() {
  // put your main code here, to run repeatedly:

//状態の切り替え  
  if (digitalRead(HI_BEAM) == LOW&&mode == CS_PLISE_MODE) {
    //HIで無ければLOW　当たり前だよなあ？
    //VSCODEモード
    key_reset();  
    mode  = VSCODE_MODE;
  }else if( digitalRead(HI_BEAM) == HIGH&&mode == VSCODE_MODE) {
    //CS＋モード
    key_reset();   
    mode  = CS_PLISE_MODE;
  }
  //方向指示器の状態取得
  if (digitalRead(TURN_R) == LOW && indicator!=RIGH_MODE) {
    //右にウインカーだしている状態に
    key_reset(); 
    indicator=RIGH_MODE;
  }else if (digitalRead(TURN_L) == LOW && indicator!=LEFT_MODE) {
    //左にウインカー出してるとき
    key_reset(); 
    indicator=LEFT_MODE;
  }else if (digitalRead(TURN_L) == HIGH && digitalRead(TURN_R) == HIGH && indicator!=CENTER) {
    //ウインカー出してないとき
    key_reset();  
    indicator=CENTER;      
  }
  //キー入力設定
  key_send_bunki();
}
//////////////////////////////////////////////////
//キー入力をすべて無しにする
//
//引き数　なし
//返り値　なし
//
////////////////////////////////////////////////
void key_reset(){
    Keyboard.releaseAll();
}


//////////////////////////////////////////////////
//キー入力を分岐させる
//
//引き数　なし
//返り値　なし
//
////////////////////////////////////////////////

void key_send_bunki(void){

  switch(mode){
///////////////////////////VSCODE操作時
    case VSCODE_MODE:
      switch(indicator){
        //ウインカーを出していないとき
        case CENTER:
          if(digitalRead(PASSING) == LOW){
             Keyboard.press(KEY_RIGHT_CTRL    );
             Keyboard.press(KEY_RIGHT_SHIFT   );
             Keyboard.press('m');
            
          }else{
             Keyboard.release(KEY_RIGHT_CTRL    );
             Keyboard.release(KEY_RIGHT_SHIFT   );  
             Keyboard.release('m'   );
                     
          }
        break;    
        //左にウインカー出しているとき
        case LEFT_MODE:
          if(digitalRead(PASSING) == LOW){
          
          }
          if(digitalRead(HORN) == LOW){

          }
        
        break;
        //右にウインカー出しているとき
        case RIGH_MODE:   
          if(digitalRead(PASSING) == LOW){
         
          }else{
        
          }
          //Ctrl+Alt+Left
          if(digitalRead(HORN) == LOW){
            
          }else{
            
          }
        
        
        break;
    }
    break;   
///////////////////////////VSCODE操作時
///////////////////////////CSPLUSE操作時
    case CS_PLISE_MODE: 
      switch(indicator){
        //ウインカー出していないとき
        case CENTER:
         if(digitalRead(HORN) == LOW){
            Keyboard.press(KEY_F7        );  
            Keyboard.release(KEY_RIGHT_SHIFT);         
          }else{
            Keyboard.press(KEY_F7        );  
            Keyboard.release(KEY_RIGHT_SHIFT);           
          }
          if(digitalRead(PASSING) == LOW){
             Keyboard.press(KEY_F6        );           
          }else{
            Keyboard.release(KEY_F6        );             
          }

        
        break;    
        //左にウインカー出してるとき
        case LEFT_MODE:   
          if(digitalRead(HORN) == LOW){
             Keyboard.press(KEY_F7        );           
          }else{
            Keyboard.release(KEY_F7        );             
          }
          if(digitalRead(PASSING) == LOW){
             Keyboard.press(KEY_F6        );           
          }else{
            Keyboard.release(KEY_F6        );             
          }

        
        break;
        //右にウインカー出しているとき
        case RIGH_MODE:   
         if(digitalRead(HORN) == LOW){
             Keyboard.press(KEY_F5        );           
          }else{
            Keyboard.release(KEY_F5        );             
          }
          if(digitalRead(PASSING) == LOW){
             Keyboard.press(KEY_F8        );           
          }else{
            Keyboard.release(KEY_F8        );             
          }


        break;
    }
    break;
  }
///////////////////////////CSPLUSE操作時 
}
