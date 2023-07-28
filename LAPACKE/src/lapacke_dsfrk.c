/*****************************************************************************
  Copyright (c) 2014, Intel Corp.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************
* Contents: Native high-level C interface to LAPACK function dsfrk
* Author: Intel Corporation
*****************************************************************************/

#include "lapacke_utils.h"

lapack_int API_SUFFIX(LAPACKE_dsfrk)( int matrix_layout, char transr, char uplo, char trans,
                          lapack_int n, lapack_int k, double alpha,
                          const double* a, lapack_int lda, double beta,
                          double* c )
{
    lapack_int ka, na;
    if( matrix_layout != LAPACK_COL_MAJOR && matrix_layout != LAPACK_ROW_MAJOR ) {
        API_SUFFIX(LAPACKE_xerbla)( "LAPACKE_dsfrk", -1 );
        return -1;
    }
#ifndef LAPACK_DISABLE_NAN_CHECK
    if( LAPACKE_get_nancheck() ) {
        /* Optionally check input matrices for NaNs */
        ka = API_SUFFIX(LAPACKE_lsame)( trans, 'n' ) ? k : n;
        na = API_SUFFIX(LAPACKE_lsame)( trans, 'n' ) ? n : k;
        if( API_SUFFIX(LAPACKE_dge_nancheck)( matrix_layout, na, ka, a, lda ) ) {
            return -8;
        }
        if( API_SUFFIX(LAPACKE_d_nancheck)( 1, &alpha, 1 ) ) {
            return -7;
        }
        if( API_SUFFIX(LAPACKE_d_nancheck)( 1, &beta, 1 ) ) {
            return -10;
        }
        if( API_SUFFIX(LAPACKE_dpf_nancheck)( n, c ) ) {
            return -11;
        }
    }
#endif
    return API_SUFFIX(LAPACKE_dsfrk_work)( matrix_layout, transr, uplo, trans, n, k, alpha,
                               a, lda, beta, c );
}
