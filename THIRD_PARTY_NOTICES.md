# Third-Party Notices

HighVoltageRobotLib is licensed under the GNU General Public License v3.0
(see [LICENSE](LICENSE)). It bundles or builds against the following
third-party components, each under its own GPLv3-compatible license:

## nlohmann/json

- License: MIT
- Upstream: https://github.com/nlohmann/json
- Vendored at `third_party/nlohmann/nlohmann/json.hpp`, header-only and
  unmodified.
- Redistributed in this library's published headers archive. `AudioPlayer.h`,
  `CommonConfig.h` and `MK5NSwerveModule.h` all include it, so it is part of
  this library's public interface and consumers cannot compile without it.
- MIT is GPLv3-compatible. The full copyright and permission notice is in the
  header of `json.hpp` and is preserved unmodified.

```
Copyright (c) 2013-2025 Niels Lohmann
```

## WPILib

- License: BSD 3-Clause
- Upstream: https://github.com/wpilibsuite/allwpilib
- **Not redistributed.** This library compiles and links against WPILib
  headers and shared libraries resolved from WPILib's Maven repositories at
  build time. Consumers obtain WPILib through their own robot project.
- BSD 3-Clause is GPLv3-compatible.

## CTRE Phoenix 6

- License: CTRE's proprietary Phoenix Software License Agreement
- Upstream: https://maven.ctr-electronics.com/
- **Not redistributed, and not linked into the published artifacts.** This
  library compiles against Phoenix6 headers (downloaded at build time to
  `build/phoenix6-headers`) and deliberately leaves CTRE symbols unresolved in
  its static library. A consuming robot project supplies and links Phoenix6
  itself, via its own CTRE vendordep and under CTRE's license.
- Because no CTRE code is distributed as part of this library, the GPLv3
  obligations of this repository do not extend to CTRE's software. A consumer
  who links both is combining GPLv3 code with CTRE's proprietary library in
  their own build; for an FRC team distributing nothing, that is a non-issue,
  but it is worth knowing before publishing a combined binary.

## Distributing binaries of this library

The published Maven artifacts contain compiled object code covered by GPLv3.
GPLv3 §6 requires that the corresponding source be made available to anyone
receiving those binaries. This is satisfied by the public source repository at
https://github.com/FRC-231/HighVoltageRobotLib, and by the `sources` archive
published alongside each release. Keep the repository public for as long as
any released binary is distributed.
