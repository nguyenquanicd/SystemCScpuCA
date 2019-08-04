#!/usr/bin/perl

#system "g++ -I. -I/cygdrive/d/20.Project/1.ModelBaseDesign/SystemC_lib32_233/include -L. -L/cygdrive/d/20.Project/1.ModelBaseDesign/SystemC_lib32_233/lib-cygwin -o test_top $ARGV[0] -lsystemc -lm";

system "g++ -I. -I/cygdrive/d/20.Project/1.ModelBaseDesign/SystemC_lib32_233/include -L. -L/cygdrive/d/20.Project/1.ModelBaseDesign/SystemC_lib32_233/lib-cygwin -o test_top *.cpp -lsystemc -lm";
__END__
