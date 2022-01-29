#ifndef __AGENTS_MIDDLEWARE_DATA_TYPES_H_
#define __AGENTS_MIDDLEWARE_DATA_TYPES_H_
namespace agents {
  namespace middleware {
    template <typename DerivedCommand>
    struct BaseCommand : DerivedCommand {

      void Execute() { static_cast<&DerivedCommand>(*this); }
    };

  } // namespace middleware
} // namespace agents
#endif