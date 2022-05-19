<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)

  Copyright (C) 2012-2020  FusionDirectory

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
*/

class term extends simplePlugin
{


  static function plInfo (): array
  {
    return [
      'plShortName'   => _('Term'),
      'plDescription' => _('Terms Settings'),
      'plObjectClass' => ['fdTaxonomyTerms'],
      'plObjectType'  => ['term' => [
        'name'        => _('Terms Lists'),
        'icon'        => 'geticon.php?context=applications&icon=term&size=16',
        'ou'          => get_ou('TaxonomyTermsRDN'),
        'mainAttr'    => 'fdTaxonomyTermCode',
        ]],
      'plSearchAttrs'  => ['description'],
      'plProvidedAcls' => parent::generatePlProvidedAcls(static::getAttributesInfo(), TRUE)
    ];
  }

  // The main function : information about attributes
  static function getAttributesInfo (): array
  {
    return [
      'main' => [
        'name'  => _('Term'),
        'attrs' => [
          new StringAttribute(
            _('Code'), _('Code name of Term'),
            'fdTaxonomyTermCode', TRUE
          ),
          new SelectAttribute(
              _('Referentiel'), _('Referentiel used'),
              'ReferentielAndTaxonomy', TRUE,
              [],
            ),
          new TextAreaAttribute(
            _('Term Long Label'), _('Long Label of Term code'),
            'fdTaxonomyTermLongLabel', FALSE
          ),
          new HiddenArrayAttribute('fdTaxonomyReferentiel',FALSE,[] ),
          new HiddenArrayAttribute('fdTaxonomyName',FALSE,[]),
          new TextAreaAttribute(
            _('Description'), _('Short description of this terms'),
            'description', FALSE
          ),
          new DateAttribute(
            _('StartDate'), _('Start Date of validity '),
            'fdTaxonomyTermStartDate', FALSE,
            'Ymd', '',
            'today', NULL
          ),
          new DateAttribute(
            _('EndDate'), _('End Date of validity'),
            'fdTaxonomyTermEndDate', FALSE,
            'Ymd', '',
            'today', NULL
          ),
        ]
      ]
    ];
  }

  function __construct ($dn = NULL, $object = NULL, $parent = NULL, $mainTab = FALSE)
  {
    global $config;

    parent::__construct($dn, $object, $parent, $mainTab);
    foreach ($config->get_cfg_value('TaxonomyList', []) as $taxonomy) {
      list($referentiel, $taxonomy,$policy,$startDate,$endDate) = explode(';', $taxonomy);
      // TODO : test the policy and the start/end Date
      $ref_tax[] = $referentiel.$config->get_cfg_value('TaxonomySeparator').$taxonomy;
    }
    $this->attributesAccess['ReferentielAndTaxonomy']->setValue($this->fdTaxonomyReferentiel[0].$config->get_cfg_value('TaxonomySeparator').$this->fdTaxonomyName[0]);
    $this->attributesAccess['ReferentielAndTaxonomy']->setChoices($ref_tax);
  }


  function compute_dn (): string
  {

    global $config;
    $refAndTex   = $this->attributesAccess['ReferentielAndTaxonomy']->getValue();
    $hRefAndTex  = explode($config->get_cfg_value('TaxonomySeparator'), $refAndTex);
    $this->fdTaxonomyReferentiel = $hRefAndTex[0];
    $this->fdTaxonomyName = $hRefAndTex[1];
    $this->ReferentielAndTaxonomy='';
    return $this->create_unique_dn('fdTaxonomyTermCode', get_ou('TaxonomyTermsRDN').$config->current['BASE']);
  }





}
