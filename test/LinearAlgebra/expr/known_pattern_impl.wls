#!/usr/bin/env wolframscript
(* ::Package:: *)

M={{0,1,2},{1,3,4},{2,4,5}}


M // TraditionalForm


w=2*M.{1,2,3}


w=4*w+2*M.{1,2,3}


H={{0,1-4*I,2-8*I},{1+4*I,3,4-16*I},{2+8*I,4+16*I,5}};
HermitianMatrixQ[H]
H // TraditionalForm


w=2*H.{1,2,3}


w=4*w+2*H.{1,2,3}


(* ::Text:: *)
(*unit triangular test*)


M={{1,1,2},{0,1,3},{0,0,1}};
M=M-IdentityMatrix[3];
M // TraditionalForm


w=2*M.{1,2,3}


w=4*w+2*Transpose[M].{1,2,3}


(* ::Text:: *)
(*unit triangular test*)


M={{1,1,2},{0,1,3},{0,0,1}};
M=M-IdentityMatrix[3];
M // TraditionalForm


w=2*M.{1,2,3}


w=4*w+2*Transpose[M].{1,2,3}


(* ::Text:: *)
(*unit triangular test*)


M={{1,1,2},{0,1,3},{0,0,1}};
M=M-IdentityMatrix[3];
M // TraditionalForm


w=2*M.{1,2,3}


w=4*w+2*Transpose[M].{1,2,3}


(* ::Text:: *)
(*triangular strict test*)


M={{1,1,2},{0,1,3},{0,0,1}};
M=M-IdentityMatrix[3];
M // TraditionalForm


w=2*M.{1,2,3}


w=4*w+2*Transpose[M].{1,2,3}


(* ::Text:: *)
(*unit triangular test*)


M={{1,1,2},{0,1,3},{0,0,1}};
M // TraditionalForm


w=2*Transpose[M].{1,2,3}


w=4*w+2*M.{1,2,3}
