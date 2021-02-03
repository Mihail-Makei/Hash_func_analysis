# Hash-function analysis
Hash-tables using separate chaining.

The main idea of the lab was to build hash-tables using separate chaining and to compare the distributions of the chain lengths on the hash value. Good hash-functions should have more or less even distribution.

# Optimization
The hash-functions were implemented both using C++ language and assembly language (x86-64).
|Time without asm, s|Time with asm, s|Optimization mode|
|-------------------|----------------|-----------------|
|12.658|1.217|-O0|
|0.986|0.880|-O1|
|0.884|0.795|-O2|
|0.872|0.783|-O3|
