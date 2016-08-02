  intptr_t literal = next_int;
  ConstantCache* cache = reinterpret_cast<ConstantCache*>(literal);

  Object* res = cache->retrieve(state, call_frame->lexical_scope());

  if(!res) {
    ConstantMissingReason reason;

    Symbol* sym = cache->name();
    res = Helpers::const_get(state, sym, &reason);

    if(reason == vFound) {
      OnStack<2> os(state, cache, res);
      if(Autoload* autoload = try_as<Autoload>(res)) {
        res = autoload->resolve(state);
      }

      if(res) {
        ConstantCache* update = ConstantCache::create(state, cache, res, call_frame->lexical_scope());
        cache->update_constant_cache(state, update);
      }
    } else {
      res = Helpers::const_missing(state, sym);
    }
  }

  CHECK_AND_PUSH(res);
