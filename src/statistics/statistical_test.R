# Script to answer question 1.1.2

# Retrieve best known values
best.known <- read.table("assets/solutions/Best-known Values", sep=" ", header=TRUE)

# 1. which initial solution is preferable?

# Retrieve the test data
files.rand <- list.files(path="src/statistics/stats/algo", pattern="ii.*rnd.*", full.names=TRUE, recursive=TRUE)
files.srz <- list.files(path="src/statistics/stats/algo", pattern="ii.*srz.*", full.names=TRUE, recursive=TRUE)

if (length(files.rand) != length(files.srz)) {
  stop("Must have same amount of file in each batch to compare one by one")
}

wilcox.result.init <- data.frame(matrix(nrow=0, ncol=5, dimnames=list(NULL, c("SimpleRZ", "SRZ.score", "Random", "Random.score", "p.value"))))

# for all pairs having only the initialisation that differs
for (i in seq_along(files.rand)) {
  files.rand[i]
  a.cost <- read.table(files.srz[i], sep=" ", header=TRUE)$Deviation
  b.cost <- read.table(files.rand[i], sep=" ", header=TRUE)$Deviation

  wilcox.result.init <- rbind(wilcox.result.init, data.frame(
    "SimpleRZ"=basename(files.srz[i]),
    "SRZ.score"=mean(a.cost),
    "Random"=basename(files.rand[i]),
    "Random.score"=mean(b.cost),
    "p.value"=wilcox.test(a.cost, b.cost, paired=TRUE)$p.value
  ))
}

write.table(wilcox.result.init, file="src/statistics/results/statistical_tests/init_wilcox", row.names=FALSE, quote=FALSE)




# 2. which pivoting rule generates better quality solutions and which is faster?

# Retrieve the test data
files.best <- list.files(path="src/statistics/stats/algo", pattern="ii.*best.*", full.names=TRUE, recursive=TRUE)
files.first <- list.files(path="src/statistics/stats/algo", pattern="ii.*first.*", full.names=TRUE, recursive=TRUE)

if (length(files.best) != length(files.first)) {
  stop("Must have same amount of file in each batch to compare one by one")
}

wilcox.result.pivot <- data.frame(matrix(nrow=0, ncol=8, dimnames=list(NULL, c("Best", "Best.score", "Best.time", "First", "First.score", "First.time", "Score.p.value", "Time.p.value"))))

# for all pairs having only the pivoting rule that differs
for (i in seq_along(files.rand)) {
  files.rand[i]
  best.cost <- read.table(files.best[i], sep=" ", header=TRUE)$Deviation
  best.time <- read.table(files.best[i], sep=" ", header=TRUE)$Time
  first.cost <- read.table(files.first[i], sep=" ", header=TRUE)$Deviation
  first.time <- read.table(files.first[i], sep=" ", header=TRUE)$Time

  wilcox.result.pivot <- rbind(wilcox.result.pivot, data.frame(
    "Best"=basename(files.best[i]),
    "Best.score"=mean(best.cost),
    "Best.time"=mean(best.time),
    "First"=basename(files.first[i]),
    "First.score"=mean(first.cost),
    "First.time"=mean(first.time),
    "Score.p.value"=wilcox.test(best.cost, first.cost, paired=TRUE)$p.value,
    "Time.p.value"=wilcox.test(best.time, first.time, paired=TRUE)$p.value
  ))
}

write.table(wilcox.result.pivot, file="src/statistics/results/statistical_tests/pivot_wilcox", row.names=FALSE, quote=FALSE)




# 3. which neighborhood generates better quality solution and what computation time is required to reach local optima?

# Retrieve the test data
files.isrt <- list.files(path="src/statistics/stats/algo", pattern="ii.*ins.*", full.names=TRUE, recursive=TRUE)
files.exch <- list.files(path="src/statistics/stats/algo", pattern="ii.*ex.*", full.names=TRUE, recursive=TRUE)
files.tran <- list.files(path="src/statistics/stats/algo", pattern="ii.*tran.*", full.names=TRUE, recursive=TRUE)

if (length(files.isrt) != length(files.exch) || length(files.isrt) != length(files.tran)) {
  stop("Must have same amount of file in each batch to compare one by one")
}

wilcox.result.neighbour <- data.frame(
  matrix(nrow=0, ncol=15, dimnames=list(
    NULL,
    c("Insert", "Exchange", "Transpose",
      "Insert.score", "Exchange.score", "Transpose.score",
      "ins.ex.score.p.value", "ins.tran.score.p.value", "ex.tran.score.p.value",
      "Insert.time", "Exchange.time", "Transpose.time",
      "ins.ex.time.p.value", "ins.tran.time.p.value", "ex.tran.time.p.value"
    )
  ))
)

# for all pairs having only the pivoting rule that differs
for (i in seq_along(files.isrt)) {
  files.rand[i]
  insert.cost <- read.table(files.isrt[i], sep=" ", header=TRUE)$Deviation
  insert.time <- read.table(files.isrt[i], sep=" ", header=TRUE)$Time

  exchange.cost <- read.table(files.exch[i], sep=" ", header=TRUE)$Deviation
  exchange.time <- read.table(files.exch[i], sep=" ", header=TRUE)$Time

  transpose.cost <- read.table(files.tran[i], sep=" ", header=TRUE)$Deviation
  transpose.time <- read.table(files.tran[i], sep=" ", header=TRUE)$Time

  wilcox.result.neighbour <- rbind(wilcox.result.neighbour, data.frame(
    "Insert"=basename(files.isrt[i]),
    "Exchange"=basename(files.exch[i]),
    "Transpose"=basename(files.tran[i]),
    "Insert.score"=mean(insert.cost),
    "Exchange.score"=mean(exchange.cost),
    "Transpose.score"=mean(transpose.cost),
    "ins.ex.score.p.value"=wilcox.test(insert.cost, exchange.cost, paired=TRUE)$p.value,
    "ins.tran.score.p.value"=wilcox.test(insert.cost, transpose.cost, paired=TRUE)$p.value,
    "ex.tran.score.p.value"=wilcox.test(exchange.cost, transpose.cost, paired=TRUE)$p.value,
    "Insert.time"=mean(insert.time),
    "Exchange.time"=mean(exchange.time),
    "Transpose.time"=mean(transpose.time),
    "ins.ex.time.p.value"=wilcox.test(insert.time, exchange.time, paired=TRUE)$p.value,
    "ins.tran.time.p.value"=wilcox.test(insert.time, transpose.time, paired=TRUE)$p.value,
    "ex.tran.time.p.value"=wilcox.test(exchange.time, transpose.time, paired=TRUE)$p.value
  ))
}

write.table(wilcox.result.neighbour, file="src/statistics/results/statistical_tests/neighbour_wilcox", row.names=FALSE, quote=FALSE)

