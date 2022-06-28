/******************************************************************** 
** ��R�� �Q�[���v���O���~���O�̊�{ 
** �i�R�j���j���[��ʂ̍쐬�i�}�E�X����Ń��j���[�I���j 
********************************************************************/ 
#include "DxLib.h" 
 
/*********************************************** 
 * �ϐ��̐錾 
 ***********************************************/ 
int g_OldKey;  // �O��̓��̓L�[ 
int g_NowKey;  // ����̓��̓L�[ 
int g_KeyFlg;  // ���̓L�[��� 
int g_MenuNumber = 0;  // ���j���[�J�[�\���ʒu 
 
int  g_MouseX;  // �}�E�X�w���W 
int  g_MouseY;  // �}�E�X�x���W 
 
int g_TitleImage; // �摜�p�ϐ� 
/*********************************************** 
 * �v���O�����̊J�n 
 ***********************************************/ 
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,  
     LPSTR lpCmdLine, int nCmdShow ) 
{ 
 // �E�B���h�E���[�h�ŋN������ 
 ChangeWindowMode(TRUE); 
 
 // DX ���C�u�����̏���������:�G���[���N�����璼���ɏI�� 
 if ( DxLib_Init() == -1 ) return -1; 
 
 //�^�C�g���摜�f�[�^�̓ǂݍ��� 
 if ((g_TitleImage = LoadGraph("images/Title2.bmp")) == -1) return -1; 
 
 // �`����ʂ𗠂ɂ��� 
 SetDrawScreen( DX_SCREEN_BACK ); 
 
 // �}�E�X�J�[�\���\�� 
 SetMouseDispFlag(TRUE); 
 
 
 
//9 
 
 // �Q�[�����[�v 
 while ( ProcessMessage() == 0 ){ 
  // �L�[���͎擾 
  g_OldKey = g_NowKey; 
  g_NowKey = GetMouseInput(); 
  g_KeyFlg = g_NowKey & ~ g_OldKey; 
   
  //�}�E�X�N���b�N�ŃQ�[�����[�h���e��ʂɐ؂�ւ��� 
  if (g_KeyFlg & MOUSE_INPUT_LEFT ) { 
   // �}�E�X������W�ǂݎ�� 
   GetMousePoint(&g_MouseX , & g_MouseY); 
   g_MenuNumber = 9; 
   // �^�C�g����ʂł̑I���i�X�^�[�g�j 
   if (g_MouseX > 120 && g_MouseX < 210 && g_MouseY > 410 && g_MouseY < 440 ) { 
    g_MenuNumber = 0; 
   } 
   // �^�C�g����ʂł̑I���i�����L���O�j  
   if (g_MouseX > 300 && g_MouseX < 410 && g_MouseY > 410 && g_MouseY < 440 ) { 
    g_MenuNumber = 1; 
   } 
   // �^�C�g����ʂł̑I��(�G���h�j 
   if (g_MouseX > 510 && g_MouseX < 555 && g_MouseY > 410 && g_MouseY < 440 ) { 
    g_MenuNumber = 2; 
   }  
  } 
  // ��ʂ̏����� 
  ClearDrawScreen(); 
 
  //�^�C�g���摜�\�� 
  DrawGraph( 0 , 0 , g_TitleImage, FALSE ) ; 
  DrawFormatString( 0, 0, GetColor( 255 , 255 , 255 ),  "MenuNumber = %d ", g_MenuNumber ); 
 
  // ����ʂ̓��e��\��ʂɔ��f���܂� 
  ScreenFlip(); 
 } 
 // DX ���C�u�����g�p�̏I������ 
 DxLib_End(); 
 
 // �\�t�g�̏I�� 
 return 0; 
} 
 