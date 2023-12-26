#include "state_machine.h"

void state_machine_init(StateMachine* state_machine) {
  state_machine->mainCamera = (Camera*)malloc(sizeof(Camera));
  state_machine->actors = NULL;
  state_machine->actorsSize = 0;
}

void state_machine_add_actor(StateMachine* state_machine, Actor** actor) {
  Actor** temp = state_machine->actors;

  state_machine->actors = (Actor**)malloc(sizeof(Actor) * (state_machine->actorsSize + 1));

  u32 i = 0;
  for (i = 0; i < state_machine->actorsSize; i++) {
    (*state_machine).actors[i] = temp[i];
  }
  state_machine->actors[i] = *actor;
  state_machine->actorsSize += 1;
}
void state_machine_remove_actor(StateMachine* state_machine, Actor* actor) {}
void state_machine_get_actor(StateMachine* state_machine, int n) {}
