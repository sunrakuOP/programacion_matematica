program nodo_demo
  implicit none

  type :: Nodo
    real(8) :: x, y, z
  end type Nodo

  type(Nodo) :: p1

  p1%x = 1.0d0
  p1%y = 2.0d0
  p1%z = 0.0d0

  print *, "p1 = (", p1%x, ",", p1%y, ",", p1%z, ")"
end program nodo_demo
