public class Main {
	public static void main(String[] args) {
		float [][] mapaPeso= {
				{1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,1,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,1,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,1,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,1,0,1},
				{1,1,1,1,1,1,1,0,1,1,1,1,1},
				{1,0,1,0,1,0,1,0,1,0,0,0,0},
				{1,1,1,1,1,1,1,0,1,1,1,1,1}
		};
		//System.out.println(mapaPeso.length);
		//System.out.println(mapaPeso[0].length);
		NodeMap geradorMap= new NodeMap(11, 13, mapaPeso); //x-> width y-> height
		
		geradorMap= new NodeMap(11, 13, mapaPeso, NodeMap.MovableDirections.FourDirections,  NodeMap.HeuristicType.EuclideanSquared);
		//System.out.println(geradorMap.calcHeuristic(0, 0, 2, 3));
		
		PathFinder pf= new PathFinder();
		//System.out.println(pf.AStar(geradorMap, 0, 0, 10, 10)); 
		int inicioX=10, inicioY=12, fimX=9, fimY=6;
		int[][] retorno = pf.AStar(geradorMap, inicioX, inicioY, fimX, fimY); 
		int tamanho = retorno.length;
		for(int i=0; i<tamanho; i++){
			System.out.println(retorno[i][0]+" "+retorno[i][1]);
		}
		/*
		retorno = RadixSort.sort(retorno);
		//System.out.println("teste");
		//System.out.println((1020/100)+" "+120%100);
//System.out.println("radix\n\n\n");
int[][] caminho=  new int[retorno.length][2];

if(inicioX<fimX && inicioY<fimY){
		for(int i=0; i<tamanho; i++){
			//System.out.print(retorno[i]);
			caminho[i][0]= (retorno[i])/100;
			caminho[i][1]= (retorno[i])%100;
			System.out.println(" node "+ i+" ("+ caminho[i][0]+", "+ caminho[i][1]+")");
		}
}else{
	for(int i=0, j=tamanho-1; j>=0; i++, j--){
		caminho[i][0]= (retorno[j])/100;
		caminho[i][1]= (retorno[j])%100;
		System.out.println(" node "+ i+" ("+ caminho[i][0]+", "+ caminho[i][1]+")");
	}
	
}
		//System.out.println(pf.AStar(geradorMap, 0, 0, 10, 10));
		*/
	}

	public static int[][] AStar(NodeMap Map, Node Start, Node End)
	//public static double[] AStar(NodeMap Map, Node Start, Node End)
	{
		if (Start != null && End != null)
		{
			if (Start.getMapParent() == Map && End.getMapParent() == Map)
			{
				boolean PathFound = true;
				BinaryHeap OpenList = new BinaryHeap();
				BinaryHeap ClosedList = new BinaryHeap();
				
				List<Node> listaCaminho = new ArrayList<Node>();
				int comecouLista=0;
				
				OpenList.add(Start);
				Start.onOpenList = true;
				while (!End.onClosedList)
				{
					if (OpenList.size() > 0)
					{
						//mexe na closedList(caminho final)
						Node Current = OpenList.remove();
						//Current.setG(Current.getG()+Current.getCost());
						System.out.println(Current.getG());
						//System.out.println(Current.getX()+" "+Current.getY());
						System.out.println(listaCaminho.size());
						if(comecouLista==0){
							listaCaminho.add(Current);
							comecouLista++;
						}else if(verifyPontos(listaCaminho.get(listaCaminho.size()-1), Current))
							listaCaminho.add(Current);
						ClosedList.add(Current);

						
						Current.onClosedList = true;
						Node[] Surrounding = Current.getSurroundingNodes();
						
						//mexe na openlist
						for (Node Next : Surrounding)
						{
							if (Next.getCost() > 0 && !Next.onClosedList)
							{
								if (!Next.onOpenList) //se nao estiver na lista de node (nos) q estamos criando
								{
									//recalcular a heuristica pode nao precisar, a cada passo
									Next.setParent(Current);
									//To do: Check to see if we are moving diagonally, if so increase the cost.
									Next.setG(Current.getG() + Next.getG());//G = Current.G + Next.Cost;
									Next.setH(Next.calcHeuristic(End));//Next.H = Next.CalcHeuristic(End);
									OpenList.add(Next);
									Next.onOpenList = true;
								}
								else //se estiver na lista de node
								{
									if (Current.getG() > (Next.getG() + Current.getCost()))
									{
										Current.setParent(Next);//Current.Parent = Next;
										Current.setG(Next.getG() + Current.getCost());//.G = Next.G + Current.Cost;
										//The way the binary heap works makes us have to remove and re-add the item.
										OpenList.remove(Current);
										OpenList.add(Current);
										//System.out.println(Current.toString());
									}
								}
							}
						}
					}
					else
					{
						PathFound = false;
						break;
					}
				}
				OpenList.clear();
				int[][] caminhoInt= new int[listaCaminho.size()][2];
				int i=0, nodeInt;
				for(Node ponto : listaCaminho){
					nodeInt= ponto.getX()*100+ponto.getY();
					caminhoInt[i][0]= (nodeInt)/100;
					caminhoInt[i][1]= (nodeInt)%100;
					++i;
				}
//				int[] caminho= new int[ClosedList.size()];
//				int k =0;
//				for(Node nodePathPercorrido: ClosedList){
//					caminho[k]= Integer.parseInt(nodePathPercorrido.toString());
//					k++;
//					//System.out.println(nodePathPercorrido.toString());
//				}
				ClosedList.clear();
				if(PathFound){
					return caminhoInt;
				}else{
					//System.out.println(Start.getX()*100+Start.getY());
					int[][] caminhoOrigem= {{Start.getX()/100},{Start.getY()%100}};
					return caminhoOrigem;
				}
				//return PathFound;
			}
			else
			{
				//throw new Exception("Start or End Node does not belong to the NodeMap passed into the function.");
			}
		}
		else
		{
			//throw new Exception("Start or End Node were not initialised, ensure they are initialised and belong to a NodeMap.");
		}

		return null;
	}