# HighVoltageRobotLib

Shared FRC robot code for Team 231 (High Voltage): swerve modules (MK4, MK5N),
a swerve drive coordinator, a PID wrapper, NetworkTables helpers, config
loading, CSV logging, debouncing and a few utilities.

## Requirements

This library is compiled against **WPILib 2026.2.1** and **Phoenix6 26.1.1**.

Phoenix6 types appear in this library's public headers, so a consuming project
**must also install the CTRE Phoenix6 vendordep**. This library ships no CTRE
binaries — its static library carries unresolved CTRE symbols that your project's
own Phoenix6 vendordep resolves at link time.

## Using it in a robot project

```bash
curl -O https://frc-231.github.io/HighVoltageRobotLib/HighVoltageRobotLib.json
mv HighVoltageRobotLib.json vendordeps/
./gradlew build
```

## Supported platforms

| Platform | Built on |
|---|---|
| `linuxathena` (roboRIO) | Ubuntu CI, cross-compiled |
| `linuxx86-64` | Ubuntu CI |
| `windowsx86-64` | Windows CI |

## Building this repository

```bash
./gradlew build -PreleaseMode
./gradlew check -PreleaseMode          # runs the GoogleTest suite
./gradlew publishToMavenLocal -PreleaseMode
```

`./gradlew installRoboRioToolchain` once, first, for the athena build.

Phoenix6 headers are downloaded from CTRE's maven and unpacked to
`build/phoenix6-headers` by the `extractPhoenix6Headers` task. The desktop test
executable additionally links real Phoenix6 shared libraries
(`extractPhoenix6TestLibs`), because it links the whole static library.

## Known issues

Each has a `DISABLED_` test in `src/test/native/cpp/`. Re-enable as fixed.

1. **`Debounce::forceValue()` does not force the value.** It sets `last_input`
   and clears `is_debouncing` but never assigns `output`, so `getValue()` keeps
   returning the stale previous output — and because a later `setValue()` with
   the same value is a no-op, the output can never catch up.
   Fix: add `output = input;`.
2. **`Debounce::operator bool()` disagrees with `getValue()`.** It returns
   `output` directly without applying the elapsed-time check and without taking
   the mutex, so it can report a stale value and races with `setValue()`.

## Test coverage

Thin, deliberately. `Debounce` is covered; `SmartPID` and `Utility` are the
natural next targets. Anything touching `TalonFX` or `CANcoder` needs a Phoenix6
simulation fixture, which is a larger piece of work.

## Versioning

One branch per season (`2026`, `2027`, ...). Releases tagged `v2026.1.0`;
pushing a `v*` tag publishes to GitHub Pages.

## Vendordep UUID

`1acfbe61-8cee-4d1f-a525-48c1df6705f0`

Generated once. **Never change it** — it is how the VS Code extension identifies
this library and detects duplicate or conflicting vendordeps.

## License

GNU General Public License v3.0 — see [LICENSE](LICENSE).

This is a **copyleft** license, and this is a **library**: a robot project that
links it forms a combined work that must also be distributed under GPLv3 if it
is distributed at all. For Team 231's own projects that is the intent. A team
that cannot accept GPLv3 should not use this library.

Note that FRC teams typically distribute nothing — code that only ever runs on
your own robot triggers no GPL obligations at all. The obligations begin when
you publish binaries or source to someone else.

Bundled third-party components and their licenses are listed in
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
