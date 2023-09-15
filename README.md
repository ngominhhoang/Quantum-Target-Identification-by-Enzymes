# QuTIE: Quantum optimization for Target Identification by Enzymes
## Introduction
Target Identification by Enzymes (TIE) problem aims to identify the set of enzymes in a given metabolic network, such
that their inhibition eliminates a given set of target compounds associated with a disease while incurring minimum
damage to the rest of the compounds. This is a NP-hard problem, and thus optimal solutions using classical computers
fail to scale to large metabolic networks. In this paper, we develop the first quantum optimization solution, called QuTIE
(Quantum optimization for Target Identification by Enzymes), to this NP-hard problem. We do that by developing an
equivalent formulation of the TIE problem in Quadratic Unconstrained Binary Optimization (QUBO) form. We then
map it to a logical graph, and embed the logical graph on a quantum hardware graph. Our experimental results on 27
metabolic networks from Escherichia coli, Homo sapiens, and Mus musculus show that QuTIE yields solutions which
are optimal or almost optimal. Our experiments also demonstrate that QuTIE can successfully identify enzyme targets
already verified in wet-lab experiments for 14 major disease classes.
## How to cite
Please cite the paper corresponding to this repository:
```
@article{10.1093/bioadv/vbad112,
    author = {Ngo, Hoang M and Thai, My T and Kahveci, Tamer},
    title = "{QuTIE: Quantum optimization for Target Identification by Enzymes}",
    journal = {Bioinformatics Advances},
    pages = {vbad112},
    year = {2023},
    month = {08},
    abstract = "{Target Identification by Enzymes (TIE) problem aims to identify the set of enzymes in a given metabolic network, such that their inhibition eliminates a given set of target compounds associated with a disease while incurring minimum damage to the rest of the compounds. This is a NP-hard problem, and thus optimal solutions using classical computers fail to scale to large metabolic networks. In this paper, we develop the first quantum optimization solution, called QuTIE (Quantum optimization for Target Identification by Enzymes), to this NP-hard problem. We do that by developing an equivalent formulation of the TIE problem in Quadratic Unconstrained Binary Optimization (QUBO) form. We then map it to a logical graph, and embed the logical graph on a quantum hardware graph. Our experimental results on 27 metabolic networks from Escherichia coli, Homo sapiens, and Mus musculus show that QuTIE yields solutions which are optimal or almost optimal. Our experiments also demonstrate that QuTIE can successfully identify enzyme targets already verified in wet-lab experiments for 14 major disease classes.}",
    issn = {2635-0041},
    doi = {10.1093/bioadv/vbad112},
    url = {https://doi.org/10.1093/bioadv/vbad112},
    eprint = {https://academic.oup.com/bioinformaticsadvances/advance-article-pdf/doi/10.1093/bioadv/vbad112/51201585/vbad112.pdf},
}
```
## How to run
