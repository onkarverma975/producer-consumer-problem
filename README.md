# producer-consumer-problem
Given the size of a circular buffer and number of readers.
Create n+1 threads
  n for readers
  1 for writers
All accessing the same circular buffer, satisfying the following the conditions:
  1. A reader cannot read in an empty location.
  2. A reader will not read from the same locatoin twice if thw writer has not overwritten.
  3. A writer cannot overwrite a place which has not been read by every reader.
  
 
