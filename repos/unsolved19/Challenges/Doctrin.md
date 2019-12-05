# Doctrin

## Given a brief description of someone’s health issues, in free text, extract relevant medical information from reliable online sources and present it in a safe and easily usable manner. 

*Originally published for Hack for Impact @Norrsken House 2019*

<https://hackforimpact.norrskenimpactweek.org>

### Author

Sonja Petrović Lundberg  <br>
CTO <br>
Doctrin


### Challenge

The healthcare system is facing a digital revolution. Whereas traditional healthcare services required the physical presence of patients, our proposal is to provide digital care when possible and physical when needed. Apart from making healthcare more accessible for patients, digital consultations, when used correctly, also allow for increased efficiency. The cost for healthcare is increasing rapidly along with problems such as long waiting times and unsustainably high stress levels among medical personnel. In order to tackle these problems, we believe in working smart and leveraging on all the possibilities digitalization has to offer. 

Digital healthcare typically starts with the patient providing information about their medical situation e.g. symptoms, medical history, demographic background. A healthcare professional then decides the next action which could be digital or physical consultation, self-care advice or emergency treatment.

Since the interaction in any case starts by the patient providing information about their medical condition, it would be possible to display relevant advice to the patient immediately. This would empower the patient and help them take additional action, if needed. In case of a life-threatening symptom or combination of symptoms, the patient might be in need of emergency care. On the other side of the spectrum, early information could help the patient to realize that self-care is the correct treatment and thus end the interaction before a healthcare professional gets involved. It could also be a stand-alone service helping patients to figure out whether or not they need professional care and, if so, what level of care.

The input and the output could be in text or voice format, adapted to different screen sizes and environments. An extension of the challenge would be to develop a multilingual solution, that provides relevant, high-quality information to the patients in their language.

### Background

Doctrin’s purpose is to radically improve healthcare and our goal is to give 1 billion people access to better healthcare. We aim to do so by helping healthcare providers to intelligently digitize the patient journey. We believe that smart digitalization can at the same time increase the medical quality, efficiency and patient satisfaction. 

Today we provide healthcare institutions with a medical information gathering system used for triage and diagnosis. We support asynchronous chat as well as video for communication and the possibility to configure the patient and clinician workflows according to different contexts and needs. The healthcare professionals often send medical advice to patients either as self-care instructions or to increase their knowledge about their medical situation and teach them to respond to changes in their condition. 

Our proposed project is to provide relevant, high-quality medical information earlier in the process and with less human involvement. This would empower the patients, while at the same time decreasing the load on healthcare professionals.There is a number of reliable, high-quality medical resources in Swedish and other languages online, but ordinary search engines do not discriminate between these and other, generic sources. Also, there are often many ways to describe the same kind of medical symptoms, but with different words, and the language used by patients often differs from the more academic language used in medical texts, which limits the usability of ordinary pattern-matching search techniques.

Some source ideas:
<br> [Vårdguiden](https://www.1177.se/)<br>
[Medibad](https://privat.medibas.se)
[Nationellt kliniskt kunskapsstöd](https://nationelltklinisktkunskapsstod.se/)<br>
[Snomed](http://www.snomed.org/)<br>
[Turning Research Into Practice](https://www.tripdatabase.com/)<br>
[List of medical wikis](https://en.wikipedia.org/wiki/List_of_medical_wikis)

Doctrin also has proprietary, anonymised medical interaction data, that can be (and has been) used for approved research projects within academia, but not shared publicly. Contact us if you have a project candidate that you think fulfills this criteria.

### Goals

Map a description of a medical condition written in free text (or voice) to the most relevant information from various online medical sources.

To solve this challenge, several different components might be needed:

* handling of input in different formats - text, structured data, language detection
* natural language processing techniques tuned for the medical domain, that can handle different synonyms, negations, attribute mapping etc. in order to extract maximum information from the input;
* [grounding techniques](https://en.wikipedia.org/wiki/Grounding_in_communication)  and UX to ensure high safety and prevent the system from giving erroneous advice, given the serious consequences this might have in the field such as medical;
* information presentation, incl. ranking, reliability grades, potentially summarisation, multi-language handling etc.;
* different methods for system configuration and source mining/adding;
* integrations with other systems/resources.

An individual hackathon project could focus on one or more of these areas.

### End-users

* Patients seeking care.
* Medical resource administrators/librarians who might want to add/map new resources to the system.

### Hashtahgs 

&#35;healthtech, #machinelearning, #nlp, #medtech, #AI</sub>


### Agenda 2030
Primarily Sustainable Development Goal(SDG) 3. Good health and wellbeing.
Implicitly also:
* SDG 5 Achieve gender equality and empower all women and girls, by lowering the threshold for at least a part of the female population to seek healthcare and get relevant, high-quality information about their healthcare issues, in a private and discrete setting
* SDG 12 Ensure sustainable consumption and production patterns, by reducing unnecessary commute to healthcare centers, and other health related material consumption
* SDG 16 Promote peaceful and inclusive societies for sustainable development, provide access to justice for all and build effective, accountable and inclusive institutions at all levels, by making healthcare institutions more effective and potentially reducing discrimination and biased handling of patients.

### Future Plans
Contributions to this challenge would make it easier for Doctrin and other providers of digital healthcare to assist patients earlied and with less dependence on the already over-strained existing healthcare providers.

A possible future product could also be an open source stand-alone app or website for medical advice retrieval, or a smart search engine built into the existing medical databases/resources.




