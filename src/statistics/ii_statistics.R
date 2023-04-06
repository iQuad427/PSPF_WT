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

wilcox.result.init.50 <- data.frame(matrix(nrow=0, ncol=5, dimnames=list(NULL, c("SimpleRZ", "SRZ.score", "Random", "Random.score", "p.value"))))
wilcox.result.init.100 <- data.frame(matrix(nrow=0, ncol=5, dimnames=list(NULL, c("SimpleRZ", "SRZ.score", "Random", "Random.score", "p.value"))))

# for all pairs having only the initialisation that differs
for (i in seq_along(files.rand)) {
  srz.cost <- read.table(files.srz[i], sep=" ", header=TRUE)
  srz.cost.50 <- subset(srz.cost, Size == 50)$Deviation
  srz.cost.100 <- subset(srz.cost, Size == 100)$Deviation

  rand.cost <- read.table(files.rand[i], sep=" ", header=TRUE)
  rand.cost.50 <- subset(rand.cost, Size == 50)$Deviation
  rand.cost.100 <- subset(rand.cost, Size == 100)$Deviation

  wilcox.result.init.50 <- rbind(wilcox.result.init.50, data.frame(
    "SimpleRZ"=basename(files.srz[i]),
    "SRZ.score"=mean(srz.cost.50),
    "Random"=basename(files.rand[i]),
    "Random.score"=mean(rand.cost.50),
    "p.value"=wilcox.test(srz.cost.50, rand.cost.50, paired=TRUE)$p.value
  ))

  wilcox.result.init.100 <- rbind(wilcox.result.init.100, data.frame(
    "SimpleRZ"=basename(files.srz[i]),
    "SRZ.score"=mean(srz.cost.100),
    "Random"=basename(files.rand[i]),
    "Random.score"=mean(rand.cost.100),
    "p.value"=wilcox.test(srz.cost.100, rand.cost.100, paired=TRUE)$p.value
  ))
}

write.table(wilcox.result.init.50, file="src/statistics/results/statistical_tests/init_wilcox_50", row.names=FALSE, quote=FALSE)
write.table(wilcox.result.init.100, file="src/statistics/results/statistical_tests/init_wilcox_100", row.names=FALSE, quote=FALSE)




# 2. which pivoting rule generates better quality solutions and which is faster?

# Retrieve the test data
files.best <- list.files(path="src/statistics/stats/algo", pattern="ii.*best.*", full.names=TRUE, recursive=TRUE)
files.first <- list.files(path="src/statistics/stats/algo", pattern="ii.*first.*", full.names=TRUE, recursive=TRUE)

if (length(files.best) != length(files.first)) {
  stop("Must have same amount of file in each batch to compare one by one")
}

wilcox.result.pivot.50 <- data.frame(matrix(nrow=0, ncol=8, dimnames=list(NULL, c("Best", "Best.score", "Best.time", "First", "First.score", "First.time", "Score.p.value", "Time.p.value"))))
wilcox.result.pivot.100 <- data.frame(matrix(nrow=0, ncol=8, dimnames=list(NULL, c("Best", "Best.score", "Best.time", "First", "First.score", "First.time", "Score.p.value", "Time.p.value"))))

# for all pairs having only the pivoting rule that differs
for (i in seq_along(files.best)) {
  best <- read.table(files.best[i], sep=" ", header=TRUE)
  first <- read.table(files.first[i], sep=" ", header=TRUE)

  best.50 <- subset(best, Size == 50)
  best.100 <- subset(best, Size == 100)
  first.50 <- subset(first, Size == 50)
  first.100 <- subset(first, Size == 100)

  best.cost.50 <- best.50$Deviation
  best.cost.100 <- best.100$Deviation
  best.time.50 <- best.50$Time
  best.time.100 <- best.100$Time
  first.cost.50 <- first.50$Deviation
  first.cost.100 <- first.100$Deviation
  first.time.50 <- first.50$Time
  first.time.100 <- first.100$Time

  wilcox.result.pivot.50 <- rbind(wilcox.result.pivot.50, data.frame(
    "Best"=basename(files.best[i]),
    "Best.score"=mean(best.cost.50),
    "Best.time"=mean(best.time.50),
    "First"=basename(files.first[i]),
    "First.score"=mean(first.cost.50),
    "First.time"=mean(first.time.50),
    "Score.p.value"=wilcox.test(best.cost.50, first.cost.50, paired=TRUE)$p.value,
    "Time.p.value"=wilcox.test(best.time.50, first.time.50, paired=TRUE)$p.value
  ))

  wilcox.result.pivot.100 <- rbind(wilcox.result.pivot.100, data.frame(
    "Best"=basename(files.best[i]),
    "Best.score"=mean(best.cost.100),
    "Best.time"=mean(best.time.100),
    "First"=basename(files.first[i]),
    "First.score"=mean(first.cost.100),
    "First.time"=mean(first.time.100),
    "Score.p.value"=wilcox.test(best.cost.100, first.cost.100, paired=TRUE)$p.value,
    "Time.p.value"=wilcox.test(best.time.100, first.time.100, paired=TRUE)$p.value
  ))
}

write.table(wilcox.result.pivot.50, file="src/statistics/results/statistical_tests/pivot_wilcox_50", row.names=FALSE, quote=FALSE)
write.table(wilcox.result.pivot.100, file="src/statistics/results/statistical_tests/pivot_wilcox_100", row.names=FALSE, quote=FALSE)




# 3. which neighborhood generates better quality solution and what computation time is required to reach local optima?

# Retrieve the test data
files.isrt <- list.files(path="src/statistics/stats/algo", pattern="ii.*ins.*", full.names=TRUE, recursive=TRUE)
files.exch <- list.files(path="src/statistics/stats/algo", pattern="ii.*ex.*", full.names=TRUE, recursive=TRUE)
files.tran <- list.files(path="src/statistics/stats/algo", pattern="ii.*tran.*", full.names=TRUE, recursive=TRUE)

if (length(files.isrt) != length(files.exch) || length(files.isrt) != length(files.tran)) {
  stop("Must have same amount of file in each batch to compare one by one")
}

wilcox.result.neighbour.50 <- data.frame(
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

wilcox.result.neighbour.100 <- data.frame(
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
  insert <- read.table(files.isrt[i], sep=" ", header=TRUE)
  insert.50 <- subset(insert, Size == 50)
  insert.100 <- subset(insert, Size == 100)

  exchange <- read.table(files.exch[i], sep=" ", header=TRUE)
  exchange.50 <- subset(exchange, Size == 50)
  exchange.100 <- subset(exchange, Size == 100)

  transpose <- read.table(files.tran[i], sep=" ", header=TRUE)
  transpose.50 <- subset(transpose, Size == 50)
  transpose.100 <- subset(transpose, Size == 100)

  insert.cost.50 <- insert.50$Deviation
  insert.cost.100 <- insert.100$Deviation
  insert.time.50 <- insert.50$Time
  insert.time.100 <- insert.100$Time

  exchange.cost.50 <- exchange.50$Deviation
  exchange.cost.100 <- exchange.100$Deviation
  exchange.time.50 <- exchange.50$Time
  exchange.time.100 <- exchange.100$Time

  transpose.cost.50 <- transpose.50$Deviation
  transpose.cost.100 <- transpose.100$Deviation
  transpose.time.50 <- transpose.50$Time
  transpose.time.100 <- transpose.100$Time

  wilcox.result.neighbour.50 <- rbind(wilcox.result.neighbour.50, data.frame(
    "Insert"=basename(files.isrt[i]),
    "Exchange"=basename(files.exch[i]),
    "Transpose"=basename(files.tran[i]),
    "Insert.score"=mean(insert.cost.50),
    "Exchange.score"=mean(exchange.cost.50),
    "Transpose.score"=mean(transpose.cost.50),
    "ins.ex.score.p.value"=wilcox.test(insert.cost.50, exchange.cost.50, paired=TRUE)$p.value,
    "ins.tran.score.p.value"=wilcox.test(insert.cost.50, transpose.cost.50, paired=TRUE)$p.value,
    "ex.tran.score.p.value"=wilcox.test(exchange.cost.50, transpose.cost.50, paired=TRUE)$p.value,
    "Insert.time"=mean(insert.time.50),
    "Exchange.time"=mean(exchange.time.50),
    "Transpose.time"=mean(transpose.time.50),
    "ins.ex.time.p.value"=wilcox.test(insert.time.50, exchange.time.50, paired=TRUE)$p.value,
    "ins.tran.time.p.value"=wilcox.test(insert.time.50, transpose.time.50, paired=TRUE)$p.value,
    "ex.tran.time.p.value"=wilcox.test(exchange.time.50, transpose.time.50, paired=TRUE)$p.value
  ))

  wilcox.result.neighbour.100 <- rbind(wilcox.result.neighbour.100, data.frame(
    "Insert"=basename(files.isrt[i]),
    "Exchange"=basename(files.exch[i]),
    "Transpose"=basename(files.tran[i]),
    "Insert.score"=mean(insert.cost.100),
    "Exchange.score"=mean(exchange.cost.100),
    "Transpose.score"=mean(transpose.cost.100),
    "ins.ex.score.p.value"=wilcox.test(insert.cost.100, exchange.cost.100, paired=TRUE)$p.value,
    "ins.tran.score.p.value"=wilcox.test(insert.cost.100, transpose.cost.100, paired=TRUE)$p.value,
    "ex.tran.score.p.value"=wilcox.test(exchange.cost.100, transpose.cost.100, paired=TRUE)$p.value,
    "Insert.time"=mean(insert.time.100),
    "Exchange.time"=mean(exchange.time.100),
    "Transpose.time"=mean(transpose.time.100),
    "ins.ex.time.p.value"=wilcox.test(insert.time.100, exchange.time.100, paired=TRUE)$p.value,
    "ins.tran.time.p.value"=wilcox.test(insert.time.100, transpose.time.100, paired=TRUE)$p.value,
    "ex.tran.time.p.value"=wilcox.test(exchange.time.100, transpose.time.100, paired=TRUE)$p.value
  ))
}

write.table(wilcox.result.neighbour.50, file="src/statistics/results/statistical_tests/neighbour_wilcox_50", row.names=FALSE, quote=FALSE)
write.table(wilcox.result.neighbour.100, file="src/statistics/results/statistical_tests/neighbour_wilcox_100", row.names=FALSE, quote=FALSE)

