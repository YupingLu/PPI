library("igraph")

dd <- read.table("plot/plot.1.kidney.txt")
gg <- graph.data.frame(dd, directed=FALSE)
png ('plot.1.kidney.png ', width = 1600 , height =1600)
plot(gg, layout=layout_with_kk, vertex.size=4, vertex.label=NA)
dev.off()

png ('plot1.45.kidney.png ', width = 1600 , height =1600)
g <- read.graph("plot/plot1.45.kidney.txt", format="edgelist", directed=FALSE, n=217)
plot(g, layout=layout_components, vertex.size=4, vertex.label=NA)
dev.off()

png ('plot2.45.kidney.png ', width = 1600 , height =1600)
g <- read.graph("plot/plot2.45.kidney.txt", format="edgelist", directed=FALSE, n=217)
plot(g, layout=layout_components, vertex.size=4, vertex.label=NA)
dev.off()
