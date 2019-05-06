# Notes on things learnt from writing csplit

## `std::chrono`

The goal of `std::chrono` is to handle conversions and time logic as much at compile time as possible. A good analogy is:
* `system_clock` is like a watch, it tells you the current time
* `steady_clock` is like a stopwatch, it's guaranteed to always increase

`high_resolution` is just whichever of the clocks has the highest resolution for now.

`csplit` uses `steady_clock` for actual timing, as it just needs a number that is guaranteed to monotonically increase. Formatting can be handled via the duration library.

`duration` represents the difference between two `time_point`s. The goal here is to use the `duration_cast` function to move between different units of time. This way, we can measure time with microsecond precision in the core, then turn it into a string using various `duration_cast`s.

`count` is a method on a `duration` which gives the raw number of units defined for the specific `duration` template parameters. It is _only_ useful for IO and should not be used for any kind of logic. Sticking with the types defined in `std::chrono` gives us a lot more compile-time safety.