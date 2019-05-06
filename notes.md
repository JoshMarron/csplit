# Notes on things learnt from writing csplit

## `std::chrono`

The goal of `std::chrono` is to handle conversions and time logic as much at compile time as possible. A good analogy is:
* `system_clock` is like a watch, it tells you the current time
* `steady_clock` is like a stopwatch, it's guaranteed to always increase

`high_resolution` is just whichever of the clocks has the highest resolution for now.

`csplit` uses `steady_clock` for actual timing, as it just needs a number that is guaranteed to monotonically increase. Formatting can be handled via the duration library.