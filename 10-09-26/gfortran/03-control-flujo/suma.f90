program suma
  implicit none
  integer :: i, total

  total = 0
  do i = 1, 10
    total = total + i
  end do

  print *, "suma 1..10 = ", total   ! esperado: 55
end program suma
