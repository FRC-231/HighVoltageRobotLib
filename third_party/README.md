# Bundled third-party code

| Component | Upstream | License |
|---|---|---|
| nlohmann/json | https://github.com/nlohmann/json | MIT |

Licensing and redistribution obligations are in
[../THIRD_PARTY_NOTICES.md](../THIRD_PARTY_NOTICES.md). This file covers the
technical details only.

## Why nlohmann/json is published in the headers zip

`AudioPlayer.h`, `CommonConfig.h` and `MK5NSwerveModule.h` all `#include
<nlohmann/json.hpp>`, so it is part of this library's **public** interface, not
an implementation detail. Consumers cannot compile against this library without
it, which is why `publish.gradle` ships it.

**This has a consequence worth knowing.** A consuming project that vendors its
own copy of nlohmann/json will have two copies on the include path, and
whichever the compiler finds first wins. If the versions differ enough, that is
an ODR violation waiting to happen.

Moving the header elsewhere does not fix this — it has to be on the consumer's
include path for our headers to compile. The only real fix is to get
`nlohmann::json` out of the public headers (forward declaration or a pimpl), at
which point it becomes a private implementation detail and stops shipping
entirely. That is a worthwhile cleanup, not a blocker.
