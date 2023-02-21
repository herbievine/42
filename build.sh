#!/bin/bash
! find . -name Makefile -type f -execdir make re \; 2>&1 | grep -FE "clang: error|Error"
