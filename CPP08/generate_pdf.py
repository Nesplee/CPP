#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import cm
from reportlab.lib import colors
from reportlab.platypus import (
    SimpleDocTemplate, Paragraph, Spacer, Table, TableStyle,
    HRFlowable, PageBreak, KeepTogether
)
from reportlab.lib.enums import TA_CENTER, TA_LEFT, TA_JUSTIFY

# ─── COULEURS ────────────────────────────────────────────────────────────────
DARK_BG     = colors.HexColor("#1e1e2e")
ACCENT      = colors.HexColor("#89b4fa")   # bleu doux
GREEN       = colors.HexColor("#a6e3a1")   # vert succès
YELLOW      = colors.HexColor("#f9e2af")   # jaune attention
RED         = colors.HexColor("#f38ba8")   # rouge erreur
MAUVE       = colors.HexColor("#cba6f7")   # mauve notion
WHITE       = colors.HexColor("#cdd6f4")
GRAY        = colors.HexColor("#585b70")
LIGHT_GRAY  = colors.HexColor("#313244")
CODE_BG     = colors.HexColor("#181825")
ORANGE      = colors.HexColor("#fab387")

W, H = A4

# ─── STYLES ──────────────────────────────────────────────────────────────────
styles = getSampleStyleSheet()

def make_style(name, parent='Normal', **kwargs):
    return ParagraphStyle(name, parent=styles[parent], **kwargs)

# Titre principal
style_main_title = make_style('MainTitle',
    fontSize=28, fontName='Helvetica-Bold', textColor=ACCENT,
    alignment=TA_CENTER, spaceAfter=6)

style_subtitle = make_style('Subtitle',
    fontSize=13, fontName='Helvetica', textColor=WHITE,
    alignment=TA_CENTER, spaceAfter=4)

style_badge = make_style('Badge',
    fontSize=10, fontName='Helvetica', textColor=GRAY,
    alignment=TA_CENTER, spaceAfter=20)

# Titres de section
style_h1 = make_style('H1',
    fontSize=18, fontName='Helvetica-Bold', textColor=ACCENT,
    spaceBefore=14, spaceAfter=6)

style_h2 = make_style('H2',
    fontSize=14, fontName='Helvetica-Bold', textColor=MAUVE,
    spaceBefore=10, spaceAfter=4)

style_h3 = make_style('H3',
    fontSize=11, fontName='Helvetica-Bold', textColor=YELLOW,
    spaceBefore=6, spaceAfter=3)

# Corps de texte
style_body = make_style('Body',
    fontSize=10, fontName='Helvetica', textColor=WHITE,
    leading=15, spaceAfter=5, alignment=TA_JUSTIFY)

style_body_small = make_style('BodySmall',
    fontSize=9, fontName='Helvetica', textColor=WHITE,
    leading=13, spaceAfter=4)

# Code
style_code = make_style('Code',
    fontSize=8.5, fontName='Courier', textColor=GREEN,
    leading=13, spaceAfter=2, leftIndent=8)

style_code_comment = make_style('CodeComment',
    fontSize=8.5, fontName='Courier', textColor=GRAY,
    leading=13, spaceAfter=2, leftIndent=8)

style_code_keyword = make_style('CodeKeyword',
    fontSize=8.5, fontName='Courier-Bold', textColor=MAUVE,
    leading=13, spaceAfter=2, leftIndent=8)

# Notion / astuce
style_notion = make_style('Notion',
    fontSize=9.5, fontName='Helvetica', textColor=WHITE,
    leading=14, leftIndent=10, rightIndent=10, spaceAfter=4)

style_bullet = make_style('Bullet',
    fontSize=9.5, fontName='Helvetica', textColor=WHITE,
    leading=14, leftIndent=16, firstLineIndent=-10, spaceAfter=3)

# ─── HELPERS ─────────────────────────────────────────────────────────────────

def hr(color=GRAY, thickness=0.5, space_before=4, space_after=8):
    return HRFlowable(width='100%', thickness=thickness, color=color,
                      spaceAfter=space_after, spaceBefore=space_before)

def notion_box(title, lines, color=MAUVE):
    """Boîte colorée pour les notions importantes."""
    content = f'<b><font color="#{color.hexval()[2:]}">▶ {title}</font></b><br/>'
    content += '<br/>'.join(lines)
    return Table(
        [[Paragraph(content, style_notion)]],
        colWidths=[W - 4*cm],
        style=TableStyle([
            ('BACKGROUND', (0,0), (-1,-1), LIGHT_GRAY),
            ('LEFTPADDING', (0,0), (-1,-1), 10),
            ('RIGHTPADDING', (0,0), (-1,-1), 10),
            ('TOPPADDING', (0,0), (-1,-1), 8),
            ('BOTTOMPADDING', (0,0), (-1,-1), 8),
            ('ROUNDEDCORNERS', [4,4,4,4]),
            ('BOX', (0,0), (-1,-1), 1, color),
        ])
    )

def code_block(lines):
    """Bloc de code avec fond sombre."""
    cells = []
    for line in lines:
        cells.append([Paragraph(line, style_code)])
    t = Table(cells, colWidths=[W - 4*cm],
        style=TableStyle([
            ('BACKGROUND', (0,0), (-1,-1), CODE_BG),
            ('LEFTPADDING', (0,0), (-1,-1), 12),
            ('RIGHTPADDING', (0,0), (-1,-1), 8),
            ('TOPPADDING', (0,0), (-1,-1), 2),
            ('BOTTOMPADDING', (0,0), (-1,-1), 2),
            ('TOPPADDING', (0,0), (0,0), 8),
            ('BOTTOMPADDING', (-1,-1), (-1,-1), 8),
            ('BOX', (0,0), (-1,-1), 1, GRAY),
        ])
    )
    return t

def section_header(text, style=style_h1):
    return KeepTogether([
        Paragraph(text, style),
        hr(ACCENT if style == style_h1 else MAUVE,
           thickness=(1 if style == style_h1 else 0.5))
    ])

def bullet(text):
    return Paragraph(f'<bullet>•</bullet> {text}', style_bullet)

# ─── CONTENU ─────────────────────────────────────────────────────────────────

story = []

# ══════════════════════════════════════════════════════════════════════════════
#  PAGE DE TITRE
# ══════════════════════════════════════════════════════════════════════════════

story.append(Spacer(1, 3*cm))
story.append(Paragraph("CPP Module 08", style_main_title))
story.append(Paragraph("Templated containers, iterators, algorithms", style_subtitle))
story.append(hr(ACCENT, thickness=1.5, space_before=8, space_after=8))
story.append(Paragraph("C++98  •  École 42  •  Présentation de soutenance", style_badge))
story.append(Spacer(1, 1.5*cm))

# Résumé des exercices
summary_data = [
    [Paragraph('<b><font color="#89b4fa">Exercice</font></b>', style_body),
     Paragraph('<b><font color="#89b4fa">Sujet</font></b>', style_body),
     Paragraph('<b><font color="#89b4fa">Notion clé</font></b>', style_body)],
    [Paragraph('ex00', style_body),
     Paragraph('easyfind', style_body),
     Paragraph('Fonction template + std::find', style_body)],
    [Paragraph('ex01', style_body),
     Paragraph('Span', style_body),
     Paragraph('Classe + méthode template + algorithmes STL', style_body)],
    [Paragraph('ex02', style_body),
     Paragraph('MutantStack', style_body),
     Paragraph('Héritage de conteneur STL + itérateurs', style_body)],
]
summary_table = Table(summary_data, colWidths=[3*cm, 4*cm, 9.5*cm])
summary_table.setStyle(TableStyle([
    ('BACKGROUND', (0,0), (-1,0), LIGHT_GRAY),
    ('BACKGROUND', (0,1), (-1,-1), CODE_BG),
    ('ROWBACKGROUNDS', (0,1), (-1,-1), [CODE_BG, LIGHT_GRAY]),
    ('BOX', (0,0), (-1,-1), 1, GRAY),
    ('INNERGRID', (0,0), (-1,-1), 0.3, GRAY),
    ('LEFTPADDING', (0,0), (-1,-1), 10),
    ('RIGHTPADDING', (0,0), (-1,-1), 10),
    ('TOPPADDING', (0,0), (-1,-1), 7),
    ('BOTTOMPADDING', (0,0), (-1,-1), 7),
]))
story.append(summary_table)

story.append(PageBreak())

# ══════════════════════════════════════════════════════════════════════════════
#  NOTIONS FONDAMENTALES
# ══════════════════════════════════════════════════════════════════════════════

story.append(section_header("Notions Fondamentales"))
story.append(Spacer(1, 0.3*cm))

# Templates
story.append(section_header("1. Les Templates (Generiques)", style_h2))
story.append(Paragraph(
    "Un <b>template</b> permet d'ecrire du code <b>generique</b> qui fonctionne avec "
    "n'importe quel type. Le compilateur genere automatiquement la version concrete "
    "de la fonction ou de la classe au moment de la compilation, selon le type utilise.",
    style_body))

story.append(notion_box("Syntaxe d'une fonction template", [
    '<font color="#a6e3a1">template &lt;typename T&gt;</font>',
    '<font color="#cdd6f4">T maFonction(T parametre) { ... }</font>',
    '',
    '<font color="#585b70">// Le compilateur genere automatiquement :</font>',
    '<font color="#cdd6f4">int maFonction(int parametre)    // si T = int</font>',
    '<font color="#cdd6f4">double maFonction(double parametre) // si T = double</font>',
]))
story.append(Spacer(1, 0.3*cm))

story.append(Paragraph(
    "<b>Regles importantes :</b>", style_h3))
story.append(bullet("L'implementation d'un template doit etre dans le <b>.hpp</b> "
    "(pas dans le .cpp), car le compilateur a besoin de voir le code complet "
    "au moment de l'instantiation."))
story.append(bullet("On peut avoir une methode template dans une classe non-template "
    "(comme dans Span avec addRange)."))
story.append(Spacer(1, 0.4*cm))

# Iterateurs
story.append(section_header("2. Les Iterateurs", style_h2))
story.append(Paragraph(
    "Un <b>iterateur</b> est un objet qui <b>pointe vers un element</b> d'un conteneur. "
    "Il abstrait le mode d'acces aux donnees : peu importe si le conteneur est "
    "un tableau, une liste chainee ou une pile, l'interface est identique.",
    style_body))

iter_data = [
    [Paragraph('<b><font color="#89b4fa">Expression</font></b>', style_body_small),
     Paragraph('<b><font color="#89b4fa">Signification</font></b>', style_body_small)],
    [Paragraph('container.begin()', style_code),
     Paragraph('Iterateur sur le PREMIER element', style_body_small)],
    [Paragraph('container.end()', style_code),
     Paragraph('Iterateur apres le DERNIER element (sentinelle)', style_body_small)],
    [Paragraph('*it', style_code),
     Paragraph('Dereference : obtient la valeur pointee', style_body_small)],
    [Paragraph('++it', style_code),
     Paragraph('Avance vers l\'element suivant', style_body_small)],
    [Paragraph('it != container.end()', style_code),
     Paragraph('Condition de fin de parcours', style_body_small)],
]
iter_table = Table(iter_data, colWidths=[5.5*cm, 11*cm])
iter_table.setStyle(TableStyle([
    ('BACKGROUND', (0,0), (-1,0), LIGHT_GRAY),
    ('ROWBACKGROUNDS', (0,1), (-1,-1), [CODE_BG, LIGHT_GRAY]),
    ('BOX', (0,0), (-1,-1), 1, GRAY),
    ('INNERGRID', (0,0), (-1,-1), 0.3, GRAY),
    ('LEFTPADDING', (0,0), (-1,-1), 10),
    ('TOPPADDING', (0,0), (-1,-1), 6),
    ('BOTTOMPADDING', (0,0), (-1,-1), 6),
]))
story.append(iter_table)
story.append(Spacer(1, 0.4*cm))

# STL Conteneurs
story.append(section_header("3. Les Conteneurs STL", style_h2))
cont_data = [
    [Paragraph('<b><font color="#89b4fa">Conteneur</font></b>', style_body_small),
     Paragraph('<b><font color="#89b4fa">Description</font></b>', style_body_small),
     Paragraph('<b><font color="#89b4fa">Acces</font></b>', style_body_small)],
    [Paragraph('std::vector&lt;T&gt;', style_code),
     Paragraph('Tableau dynamique, elements contigus en memoire', style_body_small),
     Paragraph('O(1) aleatoire', style_body_small)],
    [Paragraph('std::list&lt;T&gt;', style_code),
     Paragraph('Liste doublement chainee', style_body_small),
     Paragraph('O(n) lineaire', style_body_small)],
    [Paragraph('std::deque&lt;T&gt;', style_code),
     Paragraph('Double-ended queue, ajout rapide aux deux bouts', style_body_small),
     Paragraph('O(1) aleatoire', style_body_small)],
    [Paragraph('std::stack&lt;T&gt;', style_code),
     Paragraph('Adaptateur LIFO (Last In First Out), base sur deque', style_body_small),
     Paragraph('Pas d\'iterateurs', style_body_small)],
]
cont_table = Table(cont_data, colWidths=[4.5*cm, 9*cm, 3*cm])
cont_table.setStyle(TableStyle([
    ('BACKGROUND', (0,0), (-1,0), LIGHT_GRAY),
    ('ROWBACKGROUNDS', (0,1), (-1,-1), [CODE_BG, LIGHT_GRAY]),
    ('BOX', (0,0), (-1,-1), 1, GRAY),
    ('INNERGRID', (0,0), (-1,-1), 0.3, GRAY),
    ('LEFTPADDING', (0,0), (-1,-1), 10),
    ('TOPPADDING', (0,0), (-1,-1), 6),
    ('BOTTOMPADDING', (0,0), (-1,-1), 6),
]))
story.append(cont_table)

story.append(PageBreak())

# ══════════════════════════════════════════════════════════════════════════════
#  EX00 - EASYFIND
# ══════════════════════════════════════════════════════════════════════════════

story.append(section_header("EX00 — easyfind"))
story.append(Paragraph(
    "Implementer une <b>fonction template</b> <font name='Courier'>easyfind</font> "
    "qui cherche un entier dans n'importe quel conteneur STL sequentiel et retourne "
    "un iterateur sur l'element trouve, ou leve une exception s'il est absent.",
    style_body))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Signature", style_h2))
story.append(code_block([
    '<font color="#cba6f7">template</font> <font color="#cdd6f4">&lt;</font>'
    '<font color="#cba6f7">typename</font> <font color="#cdd6f4">T&gt;</font>',
    '<font color="#89b4fa">typename</font> <font color="#cdd6f4">T::iterator  '
    'easyfind(T &amp;container,</font> <font color="#89b4fa">int</font> '
    '<font color="#cdd6f4">value);</font>',
]))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Implementation", style_h2))
story.append(code_block([
    '<font color="#585b70">// std::find parcourt [begin, end) et retourne un iterateur</font>',
    '<font color="#585b70">// sur le premier element egal a value, ou end() si absent</font>',
    '<font color="#89b4fa">typename</font> <font color="#cdd6f4">T::iterator it = '
    '<font color="#f9e2af">std::find</font>(container.begin(), container.end(), value);</font>',
    '',
    '<font color="#cba6f7">if</font> <font color="#cdd6f4">(it == container.end())</font>',
    '<font color="#cdd6f4">    </font><font color="#cba6f7">throw</font> '
    '<font color="#cdd6f4">std::runtime_error(</font>'
    '<font color="#a6e3a1">"Value not found in container"</font>'
    '<font color="#cdd6f4">);</font>',
    '',
    '<font color="#cba6f7">return</font> <font color="#cdd6f4">it;</font>',
]))
story.append(Spacer(1, 0.3*cm))

story.append(notion_box("Pourquoi 'typename T::iterator' ?", [
    '<font color="#cdd6f4">T est un type inconnu au moment de l\'ecriture du template.</font>',
    '<font color="#cdd6f4">T::iterator pourrait etre soit un TYPE soit un membre de donnees.</font>',
    '<font color="#cdd6f4">Le mot-cle </font><font color="#cba6f7">typename</font>'
    '<font color="#cdd6f4"> indique au compilateur que c\'est un TYPE.</font>',
    '<font color="#cdd6f4">Sans ce mot-cle, le compilateur refuserait de compiler.</font>',
], MAUVE))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("std::find — Algorithme STL cle", style_h2))
algo_data = [
    [Paragraph('<b><font color="#89b4fa">Parametre</font></b>', style_body_small),
     Paragraph('<b><font color="#89b4fa">Role</font></b>', style_body_small)],
    [Paragraph('begin', style_code), Paragraph('Iterateur debut de la plage', style_body_small)],
    [Paragraph('end', style_code),   Paragraph('Iterateur fin (exclu)', style_body_small)],
    [Paragraph('value', style_code), Paragraph('Valeur a rechercher', style_body_small)],
    [Paragraph('retour', style_code),Paragraph('Iterateur sur l\'element trouve, ou end() si absent', style_body_small)],
]
t = Table(algo_data, colWidths=[4*cm, 12.5*cm])
t.setStyle(TableStyle([
    ('BACKGROUND', (0,0), (-1,0), LIGHT_GRAY),
    ('ROWBACKGROUNDS', (0,1), (-1,-1), [CODE_BG, LIGHT_GRAY]),
    ('BOX', (0,0), (-1,-1), 1, GRAY),
    ('INNERGRID', (0,0), (-1,-1), 0.3, GRAY),
    ('LEFTPADDING', (0,0), (-1,-1), 10),
    ('TOPPADDING', (0,0), (-1,-1), 6),
    ('BOTTOMPADDING', (0,0), (-1,-1), 6),
]))
story.append(t)
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Exemple d'utilisation", style_h2))
story.append(code_block([
    '<font color="#cba6f7">std::vector</font><font color="#cdd6f4">&lt;int&gt; v;</font>',
    '<font color="#cdd6f4">v.push_back(1); v.push_back(2); v.push_back(3);</font>',
    '',
    '<font color="#cba6f7">try</font> <font color="#cdd6f4">{</font>',
    '<font color="#cdd6f4">    std::vector&lt;int&gt;::iterator it = easyfind(v, 2);</font>',
    '<font color="#cdd6f4">    std::cout &lt;&lt; *it &lt;&lt; std::endl;  </font>'
    '<font color="#585b70">// affiche : 2</font>',
    '<font color="#cdd6f4">}</font> <font color="#cba6f7">catch</font>'
    '<font color="#cdd6f4"> (std::exception &amp;e) {</font>',
    '<font color="#cdd6f4">    std::cout &lt;&lt; e.what() &lt;&lt; std::endl;</font>',
    '<font color="#cdd6f4">}</font>',
]))

story.append(PageBreak())

# ══════════════════════════════════════════════════════════════════════════════
#  EX01 - SPAN
# ══════════════════════════════════════════════════════════════════════════════

story.append(section_header("EX01 — Span"))
story.append(Paragraph(
    "Creer une <b>classe Span</b> qui stocke jusqu'a N entiers et peut calculer "
    "le plus court (<i>shortestSpan</i>) et le plus long (<i>longestSpan</i>) "
    "ecart entre ses elements. La classe doit aussi accepter l'ajout en masse "
    "via une methode template <font name='Courier'>addRange</font>.",
    style_body))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Forme Canonique Orthodoxe", style_h2))
story.append(Paragraph(
    "Toute classe 42 doit implementer les <b>4 membres obligatoires</b> :", style_body))
story.append(code_block([
    '<font color="#cba6f7">class</font> <font color="#f9e2af">Span</font>',
    '<font color="#cdd6f4">{</font>',
    '<font color="#cba6f7">public</font><font color="#cdd6f4">:</font>',
    '<font color="#cdd6f4">    Span(</font><font color="#89b4fa">unsigned int</font>'
    '<font color="#cdd6f4"> N);             </font><font color="#585b70">// 1. Constructeur parametre</font>',
    '<font color="#cdd6f4">    Span(</font><font color="#cba6f7">const</font>'
    '<font color="#cdd6f4"> Span &amp;other);        </font><font color="#585b70">// 2. Constructeur de copie</font>',
    '<font color="#cdd6f4">    Span &amp;operator=(</font><font color="#cba6f7">const</font>'
    '<font color="#cdd6f4"> Span &amp;other); </font><font color="#585b70">// 3. Operateur d\'affectation</font>',
    '<font color="#cdd6f4">    ~Span();                      </font><font color="#585b70">// 4. Destructeur</font>',
    '',
    '<font color="#585b70">    // Methode template dans une classe normale :</font>',
    '<font color="#cba6f7">    template</font> <font color="#cdd6f4">&lt;</font>'
    '<font color="#cba6f7">typename</font> <font color="#cdd6f4">Iterator&gt;</font>',
    '<font color="#cdd6f4">    </font><font color="#89b4fa">void</font>'
    '<font color="#cdd6f4"> addRange(Iterator begin, Iterator end) { ... }</font>',
    '',
    '<font color="#cba6f7">private</font><font color="#cdd6f4">:</font>',
    '<font color="#cdd6f4">    </font><font color="#89b4fa">unsigned int</font>'
    '<font color="#cdd6f4">     _maxSize;   </font><font color="#585b70">// capacite max</font>',
    '<font color="#cdd6f4">    std::vector&lt;</font><font color="#89b4fa">int</font>'
    '<font color="#cdd6f4">&gt; _numbers;  </font><font color="#585b70">// les entiers stockes</font>',
    '<font color="#cdd6f4">};</font>',
]))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Algorithme shortestSpan", style_h2))
story.append(notion_box("Pourquoi trier avant de chercher le minimum ?", [
    '<font color="#cdd6f4">La plus petite difference entre deux elements QUELCONQUES</font>',
    '<font color="#cdd6f4">se trouve toujours entre deux elements ADJACENTS dans le tableau trie.</font>',
    '<font color="#cdd6f4">Exemple : [17, 3, 9, 6, 11] → trie : [3, 6, 9, 11, 17]</font>',
    '<font color="#cdd6f4">Differences adjacentes : 3, 3, 2, 6 → minimum = 2</font>',
], GREEN))
story.append(Spacer(1, 0.2*cm))
story.append(code_block([
    '<font color="#89b4fa">int</font> <font color="#cdd6f4">Span::shortestSpan()</font>'
    '<font color="#cba6f7"> const</font>',
    '<font color="#cdd6f4">{</font>',
    '<font color="#cdd6f4">    std::vector&lt;int&gt; sorted(_numbers); </font>'
    '<font color="#585b70">// copie pour ne pas modifier l\'original</font>',
    '<font color="#cdd6f4">    </font><font color="#f9e2af">std::sort</font>'
    '<font color="#cdd6f4">(sorted.begin(), sorted.end()); </font>'
    '<font color="#585b70">// tri croissant</font>',
    '',
    '<font color="#cdd6f4">    </font><font color="#89b4fa">int</font>'
    '<font color="#cdd6f4"> minSpan = sorted[1] - sorted[0];</font>',
    '<font color="#cba6f7">    for</font> <font color="#cdd6f4">(size_t i = 1; i &lt; sorted.size() - 1; ++i)</font>',
    '<font color="#cdd6f4">        minSpan = </font><font color="#f9e2af">std::min</font>'
    '<font color="#cdd6f4">(minSpan, sorted[i+1] - sorted[i]);</font>',
    '<font color="#cba6f7">    return</font> <font color="#cdd6f4">minSpan;</font>',
    '<font color="#cdd6f4">}</font>',
]))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Algorithme longestSpan", style_h2))
story.append(code_block([
    '<font color="#89b4fa">int</font> <font color="#cdd6f4">Span::longestSpan()</font>'
    '<font color="#cba6f7"> const</font>',
    '<font color="#cdd6f4">{</font>',
    '<font color="#cdd6f4">    </font><font color="#89b4fa">int</font>'
    '<font color="#cdd6f4"> maxVal = *</font><font color="#f9e2af">std::max_element</font>'
    '<font color="#cdd6f4">(_numbers.begin(), _numbers.end());</font>',
    '<font color="#cdd6f4">    </font><font color="#89b4fa">int</font>'
    '<font color="#cdd6f4"> minVal = *</font><font color="#f9e2af">std::min_element</font>'
    '<font color="#cdd6f4">(_numbers.begin(), _numbers.end());</font>',
    '<font color="#cba6f7">    return</font> <font color="#cdd6f4">maxVal - minVal;</font>',
    '<font color="#cdd6f4">}</font>',
]))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("addRange — Methode template", style_h2))
story.append(Paragraph(
    "Permet d'ajouter des elements depuis <b>n'importe quelle source</b> "
    "qui fourni des iterateurs (vector, list, tableau C...) :", style_body))
story.append(code_block([
    '<font color="#cba6f7">template</font> <font color="#cdd6f4">&lt;</font>'
    '<font color="#cba6f7">typename</font> <font color="#cdd6f4">Iterator&gt;</font>',
    '<font color="#89b4fa">void</font> <font color="#cdd6f4">addRange(Iterator begin, Iterator end)</font>',
    '<font color="#cdd6f4">{</font>',
    '<font color="#cba6f7">    for</font> <font color="#cdd6f4">(Iterator it = begin; it != end; ++it)</font>',
    '<font color="#cdd6f4">        addNumber(*it);  </font><font color="#585b70">// *it = valeur pointee</font>',
    '<font color="#cdd6f4">}</font>',
    '',
    '<font color="#585b70">// Utilisation :</font>',
    '<font color="#cdd6f4">Span bigSpan(10000);</font>',
    '<font color="#cdd6f4">std::vector&lt;int&gt; nums; </font><font color="#585b70">// rempli avec 0..9999</font>',
    '<font color="#cdd6f4">bigSpan.addRange(nums.begin(), nums.end());</font>',
]))

story.append(PageBreak())

# ══════════════════════════════════════════════════════════════════════════════
#  EX02 - MUTANTSTACK
# ══════════════════════════════════════════════════════════════════════════════

story.append(section_header("EX02 — MutantStack"))
story.append(Paragraph(
    "Creer une classe template <b>MutantStack</b> qui se comporte exactement comme "
    "<font name='Courier'>std::stack</font> (push, pop, top, size, empty) MAIS qui "
    "ajoute des <b>iterateurs</b>. La solution : heriter de std::stack et exposer "
    "les iterateurs du conteneur interne.",
    style_body))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Pourquoi std::stack n'a pas d'iterateurs ?", style_h2))
story.append(notion_box("std::stack est un adaptateur de conteneur", [
    '<font color="#cdd6f4">std::stack est une INTERFACE au-dessus d\'un autre conteneur</font>',
    '<font color="#cdd6f4">(par defaut std::deque). Il cache intentionnellement les iterateurs</font>',
    '<font color="#cdd6f4">pour forcer un acces LIFO strict (Last In First Out).</font>',
    '<font color="#cdd6f4">Seuls push(), pop(), top(), size(), empty() sont exposes.</font>',
], YELLOW))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Structure de MutantStack", style_h2))
story.append(code_block([
    '<font color="#cba6f7">template</font> <font color="#cdd6f4">&lt;</font>'
    '<font color="#cba6f7">typename</font> <font color="#cdd6f4">T&gt;</font>',
    '<font color="#cba6f7">class</font> <font color="#f9e2af">MutantStack</font>'
    '<font color="#cdd6f4"> : </font><font color="#cba6f7">public</font>'
    '<font color="#cdd6f4"> std::stack&lt;T&gt;</font>',
    '<font color="#cdd6f4">{</font>',
    '<font color="#cba6f7">public</font><font color="#cdd6f4">:</font>',
    '<font color="#585b70">    // Alias pour le type d\'iterateur du conteneur interne</font>',
    '<font color="#cba6f7">    typedef typename</font>'
    '<font color="#cdd6f4"> std::stack&lt;T&gt;::container_type::iterator       iterator;</font>',
    '<font color="#cba6f7">    typedef typename</font>'
    '<font color="#cdd6f4"> std::stack&lt;T&gt;::container_type::const_iterator const_iterator;</font>',
    '',
    '<font color="#585b70">    // "c" est le membre PROTEGE de std::stack : le conteneur interne</font>',
    '<font color="#cdd6f4">    iterator begin() { </font><font color="#cba6f7">return</font>'
    '<font color="#cdd6f4"> std::stack&lt;T&gt;::c.begin(); }</font>',
    '<font color="#cdd6f4">    iterator end()   { </font><font color="#cba6f7">return</font>'
    '<font color="#cdd6f4"> std::stack&lt;T&gt;::c.end(); }</font>',
    '<font color="#cdd6f4">};</font>',
]))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Le membre protege 'c'", style_h2))
story.append(notion_box("Acces a 'c' via l'heritage", [
    '<font color="#cdd6f4">std::stack&lt;T&gt; declare son conteneur interne comme :</font>',
    '<font color="#cba6f7">    protected</font><font color="#cdd6f4">: Container c;'
    '  // accessible depuis les classes derivees</font>',
    '',
    '<font color="#cdd6f4">Parce que MutantStack herite de std::stack,</font>',
    '<font color="#cdd6f4">on peut acceder a "c" directement.</font>',
    '<font color="#cdd6f4">c.begin() et c.end() donnent les iterateurs de la deque sous-jacente.</font>',
], ACCENT))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Exemple d'utilisation", style_h2))
story.append(code_block([
    '<font color="#cdd6f4">MutantStack&lt;</font><font color="#89b4fa">int</font>'
    '<font color="#cdd6f4">&gt; mstack;</font>',
    '<font color="#cdd6f4">mstack.push(5);   </font><font color="#585b70">// pile : [5]</font>',
    '<font color="#cdd6f4">mstack.push(17);  </font><font color="#585b70">// pile : [5, 17]</font>',
    '<font color="#cdd6f4">mstack.push(3);   </font><font color="#585b70">// pile : [5, 17, 3]</font>',
    '',
    '<font color="#585b70">// Parcours avec iterateurs (du fond vers le sommet)</font>',
    '<font color="#cdd6f4">MutantStack&lt;int&gt;::iterator it  = mstack.begin();</font>',
    '<font color="#cdd6f4">MutantStack&lt;int&gt;::iterator ite = mstack.end();</font>',
    '<font color="#cba6f7">while</font> <font color="#cdd6f4">(it != ite)</font>',
    '<font color="#cdd6f4">    std::cout &lt;&lt; *it++ &lt;&lt; std::endl;  </font>'
    '<font color="#585b70">// affiche : 5, 17, 3</font>',
]))

story.append(PageBreak())

# ══════════════════════════════════════════════════════════════════════════════
#  RECAP ALGORITHMES STL
# ══════════════════════════════════════════════════════════════════════════════

story.append(section_header("Recap — Fonctions STL Utilisees"))
story.append(Spacer(1, 0.2*cm))

stl_data = [
    [Paragraph('<b><font color="#89b4fa">Fonction</font></b>', style_body_small),
     Paragraph('<b><font color="#89b4fa">Header</font></b>', style_body_small),
     Paragraph('<b><font color="#89b4fa">Role</font></b>', style_body_small),
     Paragraph('<b><font color="#89b4fa">Retour</font></b>', style_body_small)],
    [Paragraph('std::find', style_code),
     Paragraph('<algorithm>', style_code),
     Paragraph('Cherche une valeur dans [begin, end)', style_body_small),
     Paragraph('Iterateur sur l\'element ou end()', style_body_small)],
    [Paragraph('std::sort', style_code),
     Paragraph('<algorithm>', style_code),
     Paragraph('Trie un conteneur en ordre croissant', style_body_small),
     Paragraph('void', style_code)],
    [Paragraph('std::min_element', style_code),
     Paragraph('<algorithm>', style_code),
     Paragraph('Trouve le plus petit element', style_body_small),
     Paragraph('Iterateur sur le min', style_body_small)],
    [Paragraph('std::max_element', style_code),
     Paragraph('<algorithm>', style_code),
     Paragraph('Trouve le plus grand element', style_body_small),
     Paragraph('Iterateur sur le max', style_body_small)],
]
stl_table = Table(stl_data, colWidths=[4*cm, 3*cm, 6*cm, 3.5*cm])
stl_table.setStyle(TableStyle([
    ('BACKGROUND', (0,0), (-1,0), LIGHT_GRAY),
    ('ROWBACKGROUNDS', (0,1), (-1,-1), [CODE_BG, LIGHT_GRAY]),
    ('BOX', (0,0), (-1,-1), 1, GRAY),
    ('INNERGRID', (0,0), (-1,-1), 0.3, GRAY),
    ('LEFTPADDING', (0,0), (-1,-1), 8),
    ('TOPPADDING', (0,0), (-1,-1), 6),
    ('BOTTOMPADDING', (0,0), (-1,-1), 6),
]))
story.append(stl_table)
story.append(Spacer(1, 0.6*cm))

# Questions de soutenance
story.append(section_header("Questions Frequentes en Soutenance"))
story.append(Spacer(1, 0.2*cm))

questions = [
    ("Pourquoi l'implementation du template est dans le .hpp ?",
     "Le compilateur genere le code concret au moment de l'instantiation. "
     "Il a besoin de voir l'implementation complete pour faire ca. "
     "Si elle est dans un .cpp separe, le compilateur ne peut pas la trouver."),
    ("Pourquoi utiliser 'typename T::iterator' et pas juste 'T::iterator' ?",
     "Parce que T est un type inconnu (dependant), le compilateur ne sait pas si "
     "T::iterator est un type ou un membre de donnees. Le mot-cle 'typename' "
     "lui dit explicitement que c'est un type."),
    ("Pourquoi trier avant shortestSpan ?",
     "La plus petite difference entre deux elements quelconques se trouve toujours "
     "entre deux elements adjacents apres tri. Sans tri, il faudrait comparer "
     "toutes les paires : O(n²) au lieu de O(n log n) avec le tri."),
    ("Pourquoi heriter de std::stack et pas l'encapsuler ?",
     "L'heritage permet de reutiliser toutes les methodes (push, pop, top, size, empty) "
     "sans les reecrire. Et via l'heritage, on a acces au membre protege 'c' "
     "qui contient le conteneur interne, ce qui permet d'en obtenir les iterateurs."),
    ("Que se passe-t-il si on appelle shortestSpan avec 0 ou 1 element ?",
     "La methode leve une exception std::runtime_error. On verifie _numbers.size() <= 1 "
     "au debut de la methode et on throw si c'est le cas."),
    ("addRange peut-elle lancer une exception ?",
     "Oui. Elle appelle addNumber() pour chaque element. Si le Span est plein "
     "avant la fin de la plage, addNumber() levera std::runtime_error."),
]

for q, a in questions:
    story.append(KeepTogether([
        Paragraph(f'<b><font color="#f9e2af">Q : {q}</font></b>', style_body),
        Paragraph(f'→ {a}', style_notion),
        Spacer(1, 0.25*cm),
    ]))

story.append(PageBreak())

# ══════════════════════════════════════════════════════════════════════════════
#  SCHEMA VISUEL
# ══════════════════════════════════════════════════════════════════════════════

story.append(section_header("Schemas Visuels"))
story.append(Spacer(1, 0.3*cm))

story.append(section_header("Fonctionnement d'un iterateur", style_h2))
story.append(code_block([
    '<font color="#585b70">Conteneur :  [ 10 | 20 | 30 | 40 | 50 ]</font>',
    '<font color="#585b70">               ↑                        ↑</font>',
    '<font color="#a6e3a1">            begin()                  end() (sentinelle, hors tableau)</font>',
    '',
    '<font color="#cdd6f4">it = begin()  →  *it = 10</font>',
    '<font color="#cdd6f4">++it          →  *it = 20</font>',
    '<font color="#cdd6f4">++it          →  *it = 30</font>',
    '<font color="#cdd6f4">++it          →  *it = 40</font>',
    '<font color="#cdd6f4">++it          →  *it = 50</font>',
    '<font color="#cdd6f4">++it          →   it == end()  (sortie de boucle)</font>',
]))
story.append(Spacer(1, 0.4*cm))

story.append(section_header("MutantStack — Architecture interne", style_h2))
story.append(code_block([
    '<font color="#f9e2af">MutantStack&lt;int&gt;</font>',
    '<font color="#cdd6f4">├── herite de </font><font color="#cba6f7">std::stack&lt;int&gt;</font>',
    '<font color="#cdd6f4">│   ├── push(), pop(), top(), size(), empty()</font>',
    '<font color="#cdd6f4">│   └── </font><font color="#585b70">protected: </font>'
    '<font color="#cba6f7">std::deque&lt;int&gt; c</font>'
    '<font color="#cdd6f4">   ← conteneur interne</font>',
    '<font color="#cdd6f4">│       [ 5 | 3 | 5 | 737 | 0 ]</font>',
    '<font color="#cdd6f4">│         ↑                   ↑</font>',
    '<font color="#cdd6f4">│       fond               sommet (top)</font>',
    '<font color="#cdd6f4">└── ajoute :</font>',
    '<font color="#cdd6f4">    begin() → c.begin()   (fond de la pile)</font>',
    '<font color="#cdd6f4">    end()   → c.end()     (apres le sommet)</font>',
]))
story.append(Spacer(1, 0.4*cm))

story.append(section_header("shortestSpan — Algorithme visuel", style_h2))
story.append(code_block([
    '<font color="#585b70">Entree : [17, 3, 9, 6, 11]</font>',
    '',
    '<font color="#cdd6f4">Etape 1 — Tri :       [3, 6, 9, 11, 17]</font>',
    '<font color="#cdd6f4">                       ↑  ↑  ↑   ↑   ↑</font>',
    '<font color="#cdd6f4">Etape 2 — Differences:   3  3   2   6</font>',
    '<font color="#cdd6f4">                              ↑</font>',
    '<font color="#a6e3a1">Etape 3 — Minimum :           2  ← shortestSpan</font>',
    '',
    '<font color="#f38ba8">longestSpan : max - min = 17 - 3 = 14</font>',
]))

# ══════════════════════════════════════════════════════════════════════════════
#  BUILD
# ══════════════════════════════════════════════════════════════════════════════

story.append(Spacer(1, 0.5*cm))
story.append(section_header("Commandes de Build"))
story.append(code_block([
    '<font color="#585b70"># Compiler et tester chaque exercice</font>',
    '<font color="#89b4fa">cd ex00</font> <font color="#cdd6f4">&amp;&amp; make &amp;&amp; ./easyfind</font>',
    '<font color="#89b4fa">cd ex01</font> <font color="#cdd6f4">&amp;&amp; make &amp;&amp; ./span</font>',
    '<font color="#89b4fa">cd ex02</font> <font color="#cdd6f4">&amp;&amp; make &amp;&amp; ./mutantstack</font>',
    '',
    '<font color="#585b70"># Flags utilises : -Wall -Wextra -Werror -std=c++98</font>',
]))

# ─── BUILD ───────────────────────────────────────────────────────────────────
doc = SimpleDocTemplate(
    "/home/nguyendimitri/Bureau/TRAVAIL/CURSUS/4.CPP/CPP08/CPP08_presentation.pdf",
    pagesize=A4,
    leftMargin=2*cm, rightMargin=2*cm,
    topMargin=2*cm, bottomMargin=2*cm,
)

def on_page(canvas, doc):
    canvas.saveState()
    canvas.setFillColor(DARK_BG)
    canvas.rect(0, 0, W, H, fill=1, stroke=0)
    # Numero de page
    canvas.setFillColor(GRAY)
    canvas.setFont('Helvetica', 8)
    canvas.drawRightString(W - 2*cm, 1.2*cm, f"CPP08 — page {doc.page}")
    canvas.restoreState()

doc.build(story, onFirstPage=on_page, onLaterPages=on_page)
print("PDF genere : CPP08_presentation.pdf")
