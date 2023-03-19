
best.known <- read.table("assets/solutions/Best-known Values", sep=" ", header=TRUE)

best.known$BS
#
# a.cost <- read.table("ii-best-ex-rand.dat")$value
# a.cost <- 100 * (a.cost - best.known) / best.known
# b.cost <- read.table("ii-best-ins-rand.dat")$value
# b.cost <- 100 * (b.cost - best.known) / best.known
#
# # Paired t-test
# t.test (a.cost, b.cost, paired=T)$p.value
#
# # Wilcoxon signed-rank test
# wilcox.test (a.cost, b.cost, paired=T)$p.value
