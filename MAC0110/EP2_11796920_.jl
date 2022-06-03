using Test

function testeWill()
	println("Inicio dos testes: checkWill")
		@test checkWill([0, 1]) == false
		@test checkWill([6, 1, 7, 4, 4, 7, 1, 6]) == true
		@test checkWill([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == true
		@test checkWill([0,0,0,0,0,0,0,0,0]) == false
	println("Fim dos testes: checkWill")
end

function testeTaki()
	println("Início dos teste: checkTaki")
                @test checkTaki([0, 1]) == false
                @test checkTaki([6, 1, 7, 4, 7, 7, 1, 1]) == true
                @test checkTaki([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == false
                @test checkTaki([0,0,0,0,0,0,0,0,0]) == false
	println("Fim dos teste: checkTaki")
end

function testeJackson()
        println("Início dos teste: checkJackson")
                 @test checkJackson(42, [0, 1, 4, 2]) == false
        	 @test checkJackson(10, [6, 1, 7, 4, 7, 7, 1, 1, 1, 0]) == true
        	 @test checkJackson(1000, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == false
        	 @test checkJackson(1234, [1, 2, 3, 4,0,0,0,0,0]) == false
		 @test checkJackson(1234, [6, 1, 7, 4, 7, 7, 1, 1, 1, 2, 3, 4]) == true
        println("Fim dos teste: checkJackson")
end

function testeWillBase()
        println("Início dos teste: checkWillBase")
                 @test checkWillBase(3, [0, 1, 4, 2]) == false
                 @test checkWillBase(4, [6, 1, 7, 4, 7, 7, 1, 1, 1, 0]) == false
                 @test checkWillBase(5, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == false
                 @test checkWillBase(2, [1,1,0,0,0,0,0,0,1,1,1,1,0]) == true
                 @test checkWillBase(8, [1, 4, 0, 3, 6, 9, 0]) == true
        println("Fim dos teste: checkWillBase")
end

function testeFriends()
        println("Início dos teste: checkFriends")
                 @test checkFriends([2], [2]) == nothing
                 @test checkFriends([8, 100], [6,1,7,4]) == nothing
                 @test checkFriends([42, 333],[3,3,3,4,2]) == nothing
                 @test checkFriends([24, 42, 6174], [2,4,4,2,6,1,7,4,6,1,7,4]) == []
                 @test checkFriends([1,2,3,4,5,6,7,8,9], [1,2,3,4,5,6,7,8,9,6,1,7,4,1]) == [1]
        println("Fim dos teste: checkFriends")
end



function buscabinaria(v,c)
	for i in 1: length(v)
		for j in 1: length(c)
			if v[i] == c[j]			
				c[j] = 333881
				v[i] = 333881
				break
			end
		end
		if v[i] != 333881
			return false
		end
	end
	return true
end

function checkWill(c)
        return buscabinaria([6,1,7,4], c)
end

function checkTaki(c)
	return buscabinaria([6, 1, 7, 4, 7, 7, 1, 1], c)
end

function checkJackson(x, c)
	v = [6,1,7,4,7,7,1,1]
	digito = digitos(x)
	g = unifica(v, digito)
	return buscabinaria(g,c)
end

function digitos(x)
	digito = []
	while div(x,10) != 0 || ( x > 0 && x < 10)
		valor = x % 10
		x = div(x,10)
        	push!(digito, valor)
        end
	return digito	
end

function unifica(u, v)
	resp = []
	for i in 1 : length(u)
		push!(resp, u[i])
	end
	for i in 1 : length(v)
		push!(resp, v[i])
	end
	
	return resp
end
 

function checkWillBase(base, c)
	n = mudancaBase(6174, base)
	g = digitos(n)
	return buscabinaria(g, c)
end

function mudancaBase(n, base)
   soma = 0
   pot = 1
   while n > 0
      dig = n % base
      soma = soma + dig * pot
      n = n ÷ base
      pot = pot * 10
   end
   return soma
end

function checkFriends(numbers, cards)
	v = [6,1,7,4]
	g = []
	for i in 1: length(numbers)
		v = unifica(v, digitos(numbers[i]))
	end
	
	if buscabinaria(v, cards)
		for i in 1: length(cards)
			if cards[i] != 333881
				push!(g, cards[i])
			end
		end
		return g
	end
	return nothing
end

testeWill()
testeTaki()
testeJackson()
testeWillBase()
testeFriends()
