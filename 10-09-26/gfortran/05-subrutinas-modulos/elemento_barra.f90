module elemento_barra
  implicit none
contains
  subroutine rigidez_barra(E, A, L, k)
    real(8), intent(in)  :: E, A, L
    real(8), intent(out) :: k(2,2)
    real(8) :: EA_L
    EA_L = E * A / L
    k(1,1) =  EA_L;  k(1,2) = -EA_L
    k(2,1) = -EA_L;  k(2,2) =  EA_L
  end subroutine rigidez_barra
end module elemento_barra

program principal
  use elemento_barra
  implicit none
  real(8) :: k(2,2)

  call rigidez_barra(200.0d9, 0.001d0, 2.0d0, k)   ! acero, E=200GPa, A=0.001m2, L=2m

  print *, "matriz de rigidez del elemento barra:"
  print *, k(1,:)
  print *, k(2,:)
end program principal
