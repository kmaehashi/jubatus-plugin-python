#!/bin/sh

##################################
# example usage of jubaconv
##################################

# Standard input of jubaconv must be a JSON-formatted datum.

cat << '_EOF_' | jubaconv -i datum -o fv -c config.json
{
  "num_values": {
  },
  "string_values": {
    "txt1": "The quick brown fox jumps over the lazy dog."
  },
  "binary_values": {
    "bin1": "0123456789"
  }
}
_EOF_
