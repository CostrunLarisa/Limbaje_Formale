# Limbaje Formale

Un λ − NF A este un automat finit nedeterminist care accepta si tranzitii vide.
In acest caz, functia de tranzitie se defineste astfel:
δ : Q × (Σ ∪ {λ}) → 2
Q

δ(q, λ) := λ
∗
(q) = {q}∪{p | ∃p0, p1, ...pn ∈ Q, p0 = q, pn = p, a.i. ∀i ≥ 1 ⇒ pi ∈ δ(pi−1, λ)}

i.e. p ∈ λ
∗
(q) daca si numai daca exista un drum de la q la p format din
λ-tranzitii. In acest caz, functia extinsa va avea urmatoarea definitie:

δ
∗
(q, aw) = λ
∗
(δ
∗
((δ(q, a), w)))

unde

δ(q, a) = λ
∗
(δ(λ
∗
(q), a))

Cerinte:
• permiteti functiei de citire sa considere si λ-tranzitii. Folositi pentru λ
caractere precum ”@”, ”#” sau ”.”;
• definiti functia lambdaInchidere cu signatura

s e t<i n t> LNFA : : l ambd a Inchide re ( i n t q ) ;
care calculeaza λ
∗
(q);

• rescrieti functia deltaStar, astfel incat sa respecte definitia matematica
de mai sus;
• scrieti functia main astfel incat sa puteti face un demo pentru acest proiect.
