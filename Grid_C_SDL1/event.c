//-----------------------------------------------------------------------------
// Include
//-----------------------------------------------------------------------------

#include "event.h"

//-----------------------------------------------------------------------------
// Global variable
//-----------------------------------------------------------------------------

SDL_Event event;
bool action_state[350];
int action_bindings[350];

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

void event_init(void) {
    for (int i=0; i < 350; i++) {
        action_state[i] = false;
        action_bindings[i] = A_NO_ACTION;
    }
    action_bindings[SDLK_z] = A_MOVE_FORWARD;   // w
    action_bindings[SDLK_s] = A_MOVE_BACKWARD;
    action_bindings[SDLK_q] = A_STRAFE_LEFT;    // a
    action_bindings[SDLK_d] = A_STRAFE_RIGHT;
    action_bindings[SDLK_a] = A_TURN_LEFT;      // q
    action_bindings[SDLK_e] = A_TURN_RIGHT;
    action_bindings[SDLK_f] = A_USE;
    action_bindings[SDLK_SPACE] = A_JUMP;
    action_bindings[SDLK_TAB] = A_FIRE;
}

void event_input(void) {
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            //printf("%d\n", event.key.keysym.sym);
            //printf("%d\n", event.key.keysym.unicode);
            //printf("%c\n", event.key.keysym.sym);
            action_state[action_bindings[event.key.keysym.sym]] = true;
        } else if (event.type == SDL_KEYUP) {
            action_state[action_bindings[event.key.keysym.sym]] = false;
        } else if( event.type == SDL_QUIT ) { 
            action_state[A_ESCAPE] = true;
        } 
    }
}
