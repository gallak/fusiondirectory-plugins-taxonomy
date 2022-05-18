<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)

  Copyright (C) 2013-2020 FusionDirectory

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
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
*/

class taxonomyConfig extends simplePlugin
{


  static function plInfo (): array
  {
    return [
      'plShortName'     => _('Taxonomy'),
      'plTitle'         => _('Taxonomy configuration'),
      'plDescription'   => _('FusionDirectory Taxonomy plugin configuration'),
      'plObjectClass'   => ['fdTaxonomyPluginConf'],
      'plPriority'      => 10,
      'plObjectType'    => ['configuration'],

      'plProvidedAcls'  => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }

  static function getAttributesInfo (): array
  {

      $taxonomyPolicy = [ 'opened' => 'opened', 'halfopened' => 'halfopened', 'closed' => 'closed'];

    return [
      'main' => [
        'name'  => _('Taxonomy'),
        'class' => ['fullwidth'],
        'attrs' => [
          new StringAttribute(
            _('Taxonomy RDN'), _('Branch in which Taxonomy terms will be stored'),
            'fdTaxonomyTermsRDN', TRUE,
            'ou=taxonomy'
          ),
          new StringAttribute(
            _('Taxonomy Separator'), _('String use for displaying Referential and taxonomy'),
            'fdTaxonomySeparator', TRUE,
            ' > '
          ),

        ],
      ],
      'taxonomies' => [
        'name'  => _('List of Taxonomy'),
        'class' => ['fullwidth'],
        'attrs' => [
          new OrderedArrayAttribute(
            new CharSeparatedCompositeAttribute(
              _('Taxonomy list'),
              'fdTaxonomyList',
              [
                new StringAttribute(
                  _('Referentiel'), _('Label of Referentiel'),
                  'fdTaxonomyList_TaxonomyReferentiel', TRUE
                ),
                new StringAttribute(
                  _('Taxonomy'), _('Label of Taxonomy'),
                  'fdTaxonomyList_TaxonomyLabel', TRUE
                ),
                new SelectAttribute(
                  _('policy'), _('Policy of taxonomy'),
                  'fdTaxonomyList_TaxonomyPolicy', TRUE,
                  array_keys($taxonomyPolicy), '',array_values($taxonomyPolicy)
                ),
                new DateAttribute(
                  _('StartDate'), _('Start Date of validity '),
                  'fdTaxonomyList_TaxonomyStartDate', FALSE,
                  'Ymd', '',
                  'today', NULL
                ),
                new DateAttribute(
                  _('EndDate'), _('End Date of validity'),
                  'fdTaxonomyList_TaxonomyEndDate', FALSE,
                  'Ymd', '',
                  'today', NULL
                ),

              ],
              ';',
              '',
              _('Taxonomies')
            ),
            FALSE,
            [],
            TRUE
          ),
         ],
      ]
    ];
  }

  function __construct ($dn = NULL, $object = NULL, $parent = NULL, $mainTab = FALSE)
  {
    global $config;

    parent::__construct($dn, $object, $parent, $mainTab);

 }

}
