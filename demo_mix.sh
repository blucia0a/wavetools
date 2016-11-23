#!/bin/bash

./mix.pl \
  <(./mix.pl    \
            <(./mix.pl \
                      <(./sine.pl -freq 100 -amp 0.5) \
                      <(./sine.pl -freq 190 -amp 0.5))     \
            <(./mix.pl    \
                      <(./sine.pl -freq 280 -amp 0.5) \
                      <(./sine.pl -freq 370 -amp 0.5))) \
  <(./mix.pl \
            <(./sine.pl -freq 460 -amp 0.5) \
            <(./sine.pl -freq 550 -amp 0.5))  \
| ./play.sh

