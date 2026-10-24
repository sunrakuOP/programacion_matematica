program arrays
  implicit none
  real(8) :: K(3,3), F(3), suma_K

  K = 0.0d0
  K(1,1) = 2.0d0
  K(2,2) = 2.0d0
  K(3,3) = 2.0d0

  suma_K = sum(K)                              ! sin loop -- built-in
  F = matmul(K, [1.0d0, 1.0d0, 1.0d0])          ! matriz por vector, built-in

  print *, "suma de K = ", suma_K
  print *, "F = ", F
end program arrays
