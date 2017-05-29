/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "sound.h"

int init_audio(){

if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }
	
   if (!al_reserve_samples(3)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
    

win_audio=al_load_sample( "win.wav" );
if (!win_audio){
      printf( "win Audio clip sample not loaded!\n" ); 
      return -1;
   }
lose_audio=al_load_sample( "lose.wav" );
if (!lose_audio){
      printf( "lose Audio clip sample not loaded!\n" ); 
      return -1;
   }

loop_audio=al_load_sample( "greenhill.wav" );
if (!loop_audio){
      printf( "greenhill Audio clip sample not loaded!\n" ); 
      return -1;
   }

instance1=al_create_sample_instance(win_audio);
if (!instance1){
      printf( "instance1 not created!\n" ); 
      return -1;
   }

instance2=al_create_sample_instance(lose_audio);
if (!instance2){
      printf( "instance2 not created!\n" ); 
      return -1;
   }

instance3=al_create_sample_instance(loop_audio);
if (!instance3){
      printf( "instance3 not created!\n" ); 
      return -1;
   }



if (!(al_attach_sample_instance_to_mixer(instance1,al_get_default_mixer()))){
      printf( "instance1 could not be attached!\n" ); 
      return -1;
   }
if (!(al_attach_sample_instance_to_mixer(instance2,al_get_default_mixer()))){
      printf( "instance2 could not be attached!\n" ); 
      return -1;
   }

}

void fe_end_audio(void){
    
    al_destroy_sample_instance(instance1);
    al_destroy_sample(win_audio);
    al_destroy_sample_instance(instance2);
    al_destroy_sample(lose_audio);
    al_destroy_sample_instance(instance3);
    al_destroy_sample(loop_audio);

}