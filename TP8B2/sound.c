/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "sound.h"
#include "front_end.h"

int fe_init_audio(graphic_vars_t * vars){

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


    vars->win_audio=al_load_sample( "win.wav" );
    if (!vars->win_audio){
       printf( "win Audio clip sample not loaded!\n" ); 
       return -1;
    }
    vars->lose_audio=al_load_sample( "lose.wav" );
    if (!vars->lose_audio){
        printf( "lose Audio clip sample not loaded!\n" ); 
        return -1;
    }

    vars->loop_audio=al_load_sample( "greenhill.wav" );
    if (!vars->loop_audio){
        printf( "greenhill Audio clip sample not loaded!\n" ); 
        return -1;
    }

    vars->instance1=al_create_sample_instance(vars->win_audio);
    if (!vars->instance1){
        printf( "instance1 not created!\n" ); 
        return -1;
     }

    vars->instance2=al_create_sample_instance(vars->lose_audio);
    if (!vars->instance2){
        printf( "instance2 not created!\n" ); 
        return -1;
    }

    vars->instance3=al_create_sample_instance(vars->loop_audio);
    if (!vars->instance3){
        printf( "instance3 not created!\n" ); 
        return -1;
     }

    if (!(al_attach_sample_instance_to_mixer(vars->instance1,al_get_default_mixer()))){
        printf( "instance1 could not be attached!\n" ); 
        return -1;
    }
    if (!(al_attach_sample_instance_to_mixer(vars->instance2,al_get_default_mixer()))){
        printf( "instance2 could not be attached!\n" ); 
        return -1;
    }
}
void fe_end_audio(graphic_vars_t* vars){
    
    al_destroy_sample_instance(vars->instance1);
    al_destroy_sample(vars->win_audio);
    al_destroy_sample_instance(vars->instance2);
    al_destroy_sample(vars->lose_audio);
    al_destroy_sample_instance(vars->instance3);
    al_destroy_sample(vars->loop_audio);

}