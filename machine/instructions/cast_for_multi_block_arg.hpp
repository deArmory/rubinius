  if(!call_frame->arguments) {
    Exception::internal_error(state,
                              "no arguments object");
    RUN_EXCEPTION();
  }

  /* If there is only one argument and that thing is an array...
     AND the thing being invoked is not a lambda... */
  if(!(call_frame->flags & CallFrame::cIsLambda) &&
       call_frame->arguments->total() == 1) {
    Object* obj = call_frame->arguments->get_argument(0);
    if(kind_of<Array>(obj)) {
      stack_push(obj);
    } else if(CBOOL(obj->respond_to(state, G(sym_to_ary), cFalse))) {
      obj = obj->send(state, G(sym_to_ary));
      if(!obj) RUN_EXCEPTION();
      if(kind_of<Array>(obj)) {
        stack_push(obj);
      } else {
        Exception::type_error(state, "to_ary must return an Array");
        RUN_EXCEPTION();
      }
    } else {
      Array* ary = Array::create(state, 1);
      ary->set(state, 0, obj);
      stack_push(ary);
    }
  } else {
    Array* ary = Array::create(state, call_frame->arguments->total());
    for(size_t i = 0; i < call_frame->arguments->total(); i++) {
      ary->set(state, i, call_frame->arguments->get_argument(i));
    }
    stack_push(ary);
  }
