<?php

include "trouver_sous_index.php";
include "destination.php";
include "../TD3/html_form.php";
include "soumission_multiple.php";
include "../TME2/debut_html.php";
include "../TD2/tableau_en_table.php";

$item = isset($_POST['item']) ? $_POST['item'] : 1;
$pays = isset($_POST['pays']) ? $_POST['pays'] : '';
$visite = isset($_POST['visite']) ? $_POST['visite'] : 1;
$villes = trouver_sous_index($destinations, $pays);

if (!$villes) {
    header("HTTP/1.1 303");
    header("Location: form_pays.php");
} else {
    $titre = "Bon voyage";
    if (is_numeric($item)) {
        $pays = htmlspecialchars($pays, ENT_QUOTES);
        $hidden = "<input type='hidden' name='pays' value='$pays' />";
        $hidden2 = "<input type='hidden' name='visite' value='" . ($visite+1) . "' />";
        $body = html_form(soumission_multiple($villes, $item) . $hidden . $hidden2, 'post');
    } else {
        if (isset($villes[$item]))
            $body = "Bon séjour à $item pour " . ($villes[$item] * $visite) . "€.";
        else $body = "Ville inconnue";
    }
    echo debut_html($titre),
        "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
}
?>