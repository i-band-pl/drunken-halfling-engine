#pragma once

#include "core/camera.h"
#include "core/components/actor.h"
#include "defines.h"

typedef struct {
  Actor** actors;
  i32 actorsSize;

  Camera* mainCamera;
} StateMachine;

void state_machine_init(StateMachine* state_machine);

DHAPI void state_machine_add_actor(StateMachine* state_machine, Actor** actor);
DHAPI void state_machine_remove_actor(StateMachine* state_machine, Actor* actor);
DHAPI void state_machine_get_actor(StateMachine* state_machine, int n);