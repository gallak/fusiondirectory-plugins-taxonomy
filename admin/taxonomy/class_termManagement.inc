<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)

  Copyright (C) 2012-2019  FusionDirectory

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

class termManagement extends management
{
  public static $skipTemplates = FALSE;

  public static $columns = [
    ['ObjectTypeColumn', []],
    ['LinkColumn',       ['attributes' => 'fdTaxonomyCode',              'label' => 'Name']],
    ['LinkColumn',       ['attributes' => 'fdTaxonomyReferentiel', 'label' => 'Referentiel']],
    ['LinkColumn',       ['attributes' => 'fdTaxonomyName',        'label' => 'Taxonomy']],
    ['LinkColumn',       ['attributes' => 'description',           'label' => 'Description']],
    ['ActionsColumn',    ['label' => 'Actions']],
  ];

  static function plInfo (): array
  {
    return [
      'plShortName'   => _('Taxonomy terms'),
      'plDescription' => _('Taxonomy terms management'),
      'plIcon'        => 'geticon.php?context=applications&icon=term&size=48',
      'plSection'     => 'accounts',
      'plPriority'    => 40,
      'plManages'     => ['term'],
      'plProvidedAcls' => []
    ];
  }

  protected function setUpListing ()
  {
    /* Set baseMode to FALSE */
    $this->listing  = new managementListing($this, FALSE);
  }
}
