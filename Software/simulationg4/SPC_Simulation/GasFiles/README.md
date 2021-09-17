## Magboltz Gas Files Collection ##

gasFile_XXX_YYY_El1_F1_El2.gas
XXX: Pressure
YYY: ncol
El1 : element 1
F1 : fraction of Element 1 in %
El2: element 2

## WARNING ##
Be careful when using a file for lower pressure than it was produced with.
All files were produced in the E range (0.01 - 100e3)V/cm.
However, the important variable is the E/P. This means that when going
to lower pressure than the one used in the calculation (and depending
on the electric field of the detector) you may end up in
extrapolating, which is not to be trusted.

In general, using a file for a higher pressure than that it was
produced with is safer. One may end up with extrolation at the low-E
side, but this area is a bit less dramatic. 

Anyways, beware!

## Pure Gases ##
gasFile_760_100_Xe.gas
gasFile_760_100_CF4.gas
gasFile_760_100_Ar.gas
gasFile_760_50_CH4.gas
gasFile_760_50_N2.gas
gasFile_760_50_Ne.gas

gasFile_100_50_CH4.gas

## Ar:CF4 ##
gasFile_760_50_Ar_90_CF4.gas
gasFile_760_50_Ar_80_CF4.gas
gasFile_760_50_Ar_70_CF4.gas
gasFile_760_50_Ar_60_CF4.gas
gasFile_760_50_Ar_50_CF4.gas
gasFile_760_50_Ar_40_CF4.gas
gasFile_760_50_Ar_30_CF4.gas
gasFile_760_100_Ar_20_CF4.gas
gasFile_760_100_Ar_10_CF4.gas

gasFile_100_50_Ar_80_CF4.gas

## Ar:CH4 ##
gasFile_760_50_Ar_98_CH4.gas 
gasFile_760_50_Ar_95_CH4.gas 
gasFile_760_50_Ar_90_CH4.gas
gasFile_760_50_Ar_80_CH4.gas
gasFile_760_50_Ar_70_CH4.gas
gasFile_760_50_Ar_60_CH4.gas
gasFile_760_50_Ar_50_CH4.gas
gasFile_760_50_Ar_40_CH4.gas
gasFile_760_50_Ar_30_CH4.gas
gasFile_760_50_Ar_20_CH4.gas
gasFile_760_50_Ar_10_CH4.gas

gasFile_150_50_Ar_98_CH4.gas

## Impurities ##
gasFile_760_50_Ar_98_CH4_imp_O2_20.gas
gasFile_760_50_Ar_98_CH4_imp_O2_10.gas
gasFile_760_50_Ar_98_CH4_imp_O2_5.gas
gasFile_760_50_Ar_98_CH4_imp_O2_1.gas
gasFile_760_50_Ar_98_CH4_imp_O2_0p5.gas
gasFile_760_50_Ar_98_CH4_imp_O2_0p1.gas

an effort for produce
```gasFile_7600_50_Ar_98_CH4_imp_O2_20.gas``` in the hope to smooth out
attachment for 760Torr, did not seem to work very
well in terms of attachment..



## Submitted Files ##
gasFile_760_50_Xe_imp_O2_20.gas
gasFile_760_50_Xe_imp_O2_10.gas
gasFile_760_50_Xe_imp_O2_5.gas


## Requested Files ##
He_90_CH4
Ne_94_CH4
Ne_99p3_CH4

