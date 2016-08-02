  intptr_t depth = next_int;
  intptr_t index = next_int;
  if(depth == 0) {
    Exception::internal_error(state,
                              "illegal push_local_depth usage");
    RUN_EXCEPTION();
  } else {
    VariableScope* scope = call_frame->scope->parent();

    if(!scope || scope->nil_p()) {
      Exception::internal_error(state,
                                "illegal push_local_depth usage, no parent");
      RUN_EXCEPTION();
    }

    for(int j = 1; j < depth; j++) {
      scope = scope->parent();
      if(!scope || scope->nil_p()) {
        Exception::internal_error(state,
                                  "illegal push_local_depth usage, no parent");
        RUN_EXCEPTION();
      }
    }

    if(index >= scope->number_of_locals()) {
      Exception::internal_error(state,
                                "illegal push_local_depth usage, bad index");
      RUN_EXCEPTION();
    }

    stack_push(scope->get_local(state, index));
  }
