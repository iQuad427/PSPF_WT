# Script to answer question 1.2

# Retrieve best known values
best.known <- read.table("assets/solutions/Best-known Values", sep=" ", header=TRUE)

# a) Stats on VND + comparison with II

files.vnd <- list.files(path="out/vnd/", pattern="vnd.*tran.*(ex|ins).*", full.names=TRUE, recursive=TRUE)

vnd.result <- data.frame(matrix(nrow=0, ncol=6, dimnames=list(NULL, c("Algo", "Size", "Deviation", "Time", "ins.improve", "ex.improve"))))

for (algo in files.vnd) {
  # Get algorithm results
  score.instances <- read.table(algo, sep=" ", header=TRUE)

   # Average the values for solution score and execution time w.r.t the instance
  mean.result <- aggregate(cbind(Score, Time) ~ Instance + Size, data=score.instances, FUN=mean)

  # Compute the relative percentage deviation
  instance.cost <- 100 * (mean.result$Score - best.known$Value) / best.known$Value

  if (grepl(".*srz.*", basename(algo))) {
    if (grepl(".*first.*", basename(algo))) {
      file.ii.ins <- "out/ii/ii-first-srz-ins"
      file.ii.ex <- "out/ii/ii-first-srz-ex"
    } else if (grepl(".*best.*", basename(algo))) {
      file.ii.ins <- "out/ii/ii-best-srz-ins"
      file.ii.ex <- "out/ii/ii-best-srz-ex"
    }
  } else if (grepl(".*rnd.*", basename(algo))) {
    if (grepl(".*first.*", basename(algo))) {
      file.ii.ins <- "out/ii/ii-first-rnd-ins"
      file.ii.ex <- "out/ii/ii-first-rnd-ex"
    } else if (grepl(".*best.*", basename(algo))) {
      file.ii.ins <- "out/ii/ii-best-rnd-ins"
      file.ii.ex <- "out/ii/ii-best-rnd-ex"
    }

  }

  ii.ins <- read.table(file.ii.ins, sep=" ", header=TRUE)
  ii.ins.mean <- aggregate(cbind(Score, Time) ~ Instance + Size, data=ii.ins, FUN=mean)
  ii.ex <- read.table(file.ii.ex, sep=" ", header=TRUE)
  ii.ex.mean <- aggregate(cbind(Score, Time) ~ Instance + Size, data=ii.ex, FUN=mean)

  ins.dev <- 100 * (ii.ins.mean$Score - mean.result$Score) / ii.ins.mean$Score
  ex.dev <- 100 * (ii.ex.mean$Score - mean.result$Score) / ii.ex.mean$Score

  result <- data.frame(
    "Algo"=basename(algo),
    "Size"=mean.result$Size,
    "Deviation"=instance.cost,
    "Time"=mean.result$Time,
    "ins.improve"=ins.dev,
    "ex.improve"=ex.dev
  )

  vnd.result <- rbind(vnd.result, result)
}

# Average the values for solution derivation and execution time w.r.t to the size of the instance
vnd.result <- aggregate(. ~ Algo + Size, data=vnd.result, FUN=mean)

# Create output files for the results
write.table(vnd.result, file=paste0("src/statistics/results/vnd/", "vnd_improvement"), row.names=FALSE, quote=FALSE)

# b) Comparison between VND algorithms

# i. simple_rz vs. random

# Retrieve the test data
files.rand <- list.files(path="src/statistics/stats/algo", pattern="vnd.*rnd.*", full.names=TRUE, recursive=TRUE)
files.srz <- list.files(path="src/statistics/stats/algo", pattern="vnd.*srz.*", full.names=TRUE, recursive=TRUE)

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

write.table(wilcox.result.init.50, file="src/statistics/results/vnd/init_wilcox_50", row.names=FALSE, quote=FALSE)
write.table(wilcox.result.init.100, file="src/statistics/results/vnd/init_wilcox_100", row.names=FALSE, quote=FALSE)


# ii. tran -> ins -> ex vs. tran -> ex -> ins

# Retrieve the test data
files.ins.ex <- list.files(path="src/statistics/stats/algo", pattern="vnd.*tran-ins-ex.*", full.names=TRUE, recursive=TRUE)
files.ex.ins <- list.files(path="src/statistics/stats/algo", pattern="vnd.*tran-ex-ins.*", full.names=TRUE, recursive=TRUE)

if (length(files.ins.ex) != length(files.ex.ins)) {
  stop("Must have same amount of file in each batch to compare one by one")
}

wilcox.result.neigh.50 <- data.frame(matrix(nrow=0, ncol=5, dimnames=list(NULL, c("SimpleRZ", "SRZ.score", "Random", "Random.score", "p.value"))))
wilcox.result.neigh.100 <- data.frame(matrix(nrow=0, ncol=5, dimnames=list(NULL, c("SimpleRZ", "SRZ.score", "Random", "Random.score", "p.value"))))

# for all pairs having only the initialisation that differs
for (i in seq_along(files.ins.ex)) {
  ins.ex.cost <- read.table(files.ins.ex[i], sep=" ", header=TRUE)
  ins.ex.cost.50 <- subset(ins.ex.cost, Size == 50)$Deviation
  ins.ex.cost.100 <- subset(ins.ex.cost, Size == 100)$Deviation

  ex.ins.cost <- read.table(files.ex.ins[i], sep=" ", header=TRUE)
  ex.ins.cost.50 <- subset(ex.ins.cost, Size == 50)$Deviation
  ex.ins.cost.100 <- subset(ex.ins.cost, Size == 100)$Deviation

  wilcox.result.neigh.50 <- rbind(wilcox.result.neigh.50, data.frame(
    "ins.ex"=basename(files.ins.ex[i]),
    "ins.ex.score"=mean(ins.ex.cost.50),
    "ex.ins"=basename(files.ex.ins[i]),
    "ex.ins.score"=mean(ex.ins.cost.50),
    "p.value"=wilcox.test(ins.ex.cost.50, ex.ins.cost.50, paired=TRUE)$p.value
  ))

  wilcox.result.neigh.100 <- rbind(wilcox.result.neigh.100, data.frame(
    "ins.ex"=basename(files.ins.ex[i]),
    "ins.ex.score"=mean(ins.ex.cost.100),
    "ex.ins"=basename(files.ex.ins[i]),
    "ex.ins.score"=mean(ex.ins.cost.100),
    "p.value"=wilcox.test(ins.ex.cost.100, ex.ins.cost.100, paired=TRUE)$p.value
  ))
}

write.table(wilcox.result.neigh.50, file="src/statistics/results/vnd/neigh_wilcox_50", row.names=FALSE, quote=FALSE)
write.table(wilcox.result.neigh.100, file="src/statistics/results/vnd/neigh_wilcox_100", row.names=FALSE, quote=FALSE)


# iii. best vs. first

# Retrieve the test data
files.best <- list.files(path="src/statistics/stats/algo", pattern="vnd.*best.*", full.names=TRUE, recursive=TRUE)
files.first <- list.files(path="src/statistics/stats/algo", pattern="vnd.*first.*", full.names=TRUE, recursive=TRUE)

if (length(files.best) != length(files.first)) {
  stop("Must have same amount of file in each batch to compare one by one")
}

wilcox.result.pivot.50 <- data.frame(matrix(nrow=0, ncol=5, dimnames=list(NULL, c("Best", "Best.score", "First", "First.score", "p.value"))))
wilcox.result.pivot.100 <- data.frame(matrix(nrow=0, ncol=5, dimnames=list(NULL, c("Best", "Best.score", "First", "First.score", "p.value"))))

# for all pairs having only the initialisation that differs
for (i in seq_along(files.ins.ex)) {
  best.cost <- read.table(files.best[i], sep=" ", header=TRUE)
  best.cost.50 <- subset(best.cost, Size == 50)$Deviation
  best.cost.100 <- subset(best.cost, Size == 100)$Deviation

  first.cost <- read.table(files.first[i], sep=" ", header=TRUE)
  first.cost.50 <- subset(first.cost, Size == 50)$Deviation
  first.cost.100 <- subset(first.cost, Size == 100)$Deviation

  wilcox.result.pivot.50 <- rbind(wilcox.result.pivot.50, data.frame(
    "ins.ex"=basename(files.best[i]),
    "ins.ex.score"=mean(best.cost.50),
    "ex.ins"=basename(files.first[i]),
    "ex.ins.score"=mean(first.cost.50),
    "p.value"=wilcox.test(best.cost.50, first.cost.50, paired=TRUE)$p.value
  ))

  wilcox.result.pivot.100 <- rbind(wilcox.result.pivot.100, data.frame(
    "ins.ex"=basename(files.best[i]),
    "ins.ex.score"=mean(best.cost.100),
    "ex.ins"=basename(files.first[i]),
    "ex.ins.score"=mean(first.cost.100),
    "p.value"=wilcox.test(best.cost.100, first.cost.100, paired=TRUE)$p.value
  ))
}

write.table(wilcox.result.pivot.50, file="src/statistics/results/vnd/pivot_wilcox_50", row.names=FALSE, quote=FALSE)
write.table(wilcox.result.pivot.100, file="src/statistics/results/vnd/pivot_wilcox_100", row.names=FALSE, quote=FALSE)
