# libcmem changelog

***v 0.21***
    - Allowing static linking for chunk arrays.
    - Fixed free list obsucre problems with linking.
    - Changed cm_chunk_pop to be index based instead of pointer based.

***v 0.20***
    - Removed iterators, no longer usable with dynamic free.
    - Arena implementation starting, still in progress.
    - minor changes.

***v 0.13***: 
    - Free list implementation. BROKE ITERATORS MADGE.
    - Fixed line padding detection in 24bpp bitmap parsing.
    - Chunk linkage is now effective in accessors/utils.

***v 0.12***: 
    - Added linking of chunks, maybe not perfect but fixes coming if any.

***v 0.11***: 
    - Added limg implementation to parse bitmaps (see libterm if the repo is public ?).

***v 0.1***: 
    - initial version. nothing changed since previous...
